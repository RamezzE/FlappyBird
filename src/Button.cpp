#include "Button.hpp"

#include <iostream>

Button::Button()
{
    init();
}

Button::Button(sf::Texture &texture)
{
    sprite.setTexture(texture);
    init();
}

void Button::init()
{
    mouseOver = false;
    pressed = false;
    pressedColor = sf::Color(178, 178, 178);
    hoverColor = sf::Color(220, 220, 220);

    onAction = []() {};
}

void Button::setPressedColor(sf::Color color)
{
    pressedColor = color;
}

void Button::setScale(sf::Vector2f scale)
{
    sprite.setScale(scale);
}

void Button::setTexture(sf::Texture &texture)
{
    sprite.setTexture(texture);
}

void Button::setOrigin(sf::Vector2f origin)
{
    sprite.setOrigin(origin);
}

void Button::handleInput(sf::Event event)
{
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
            if (mouseOver) 
                onAction();
            break;
        }
        pressed = false;
    }
}

void Button::update(sf::RenderWindow *window)
{
    if (Input::isMouseOver(sprite, window))
        mouseOver = true;
    else
        mouseOver = false;
}

void Button::render(sf::RenderWindow *window)
{
    
    if (pressed)
        sprite.setColor(pressedColor);
    else if (mouseOver)
        sprite.setColor(hoverColor);
    else
        sprite.setColor(sf::Color::White);

    window->draw(sprite);
}

void Button::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
}

sf::FloatRect Button::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}

sf::FloatRect Button::getLocalBounds()
{
    return sprite.getLocalBounds();
}

void Button::setOnAction(const std::function<void()> &callback)
{
    onAction = callback;
}

std::function<void()> Button::getOnAction()
{
    return onAction;
}

bool Button::isMouseOver()
{
    return mouseOver;
}