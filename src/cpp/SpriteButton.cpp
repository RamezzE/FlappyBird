#include "../hpp/SpriteButton.hpp"

#include <iostream>

SpriteButton::SpriteButton()
{
    init();
}

SpriteButton::SpriteButton(sf::Texture &texture)
{
    sprite.setTexture(texture);
    init();
}

void SpriteButton::init()
{
    mouseOver = pressed = disabled = false;

    disabledColor = sf::Color(128, 128, 128);
    pressedColor = sf::Color(178, 178, 178);
    hoverColor = sf::Color(220, 220, 220);

    onAction = []() {};
    buttonClickSoundBuffer.loadFromFile(BUTTON_CLICK_SOUND);
    buttonClickSound.setBuffer(buttonClickSoundBuffer);
    buttonClickSound.setVolume(50);
}

void SpriteButton::setPressedColor(sf::Color color)
{
    pressedColor = color;
}

void SpriteButton::setScale(sf::Vector2f scale)
{
    sprite.setScale(scale);
}

void SpriteButton::setTexture(sf::Texture &texture)
{
    sprite.setTexture(texture);
}

void SpriteButton::setOrigin(sf::Vector2f origin)
{
    sprite.setOrigin(origin);
}

void SpriteButton::handleInput(sf::Event event)
{
    if (disabled)
        return;

    if (event.type == sf::Event::MouseButtonPressed)
    {
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (mouseOver)
                pressed = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (mouseOver) {
                onAction();
                buttonClickSound.play();
            }
            break;
        }
        pressed = false;
    }
}

void SpriteButton::update(sf::RenderWindow *window)
{
    if (disabled) {
        mouseOver = pressed = false;
        return;
    }
        
    if (Input::isMouseOver(sprite, window))
        mouseOver = true;
    else
        mouseOver = false;
}

void SpriteButton::render(sf::RenderWindow *window)
{
    if (disabled)
        sprite.setColor(disabledColor);
    else if (pressed)
        sprite.setColor(pressedColor);
    else if (mouseOver)
        sprite.setColor(hoverColor);
    else
        sprite.setColor(sf::Color::White);

    window->draw(sprite);
}

void SpriteButton::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
}

void SpriteButton::setDisabled(bool disabled)
{
    this->disabled = disabled;
}

sf::FloatRect SpriteButton::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}

sf::FloatRect SpriteButton::getLocalBounds()
{
    return sprite.getLocalBounds();
}

sf::Vector2f SpriteButton::getPosition()
{
    return sprite.getPosition();
}

void SpriteButton::setOnAction(const std::function<void()> &callback)
{
    onAction = callback;
}

std::function<void()> SpriteButton::getOnAction()
{
    return onAction;
}

bool SpriteButton::isMouseOver()
{
    return mouseOver;
}