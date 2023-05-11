#include "Button.hpp"

Button::Button(sf::Texture &texture, sf::RenderWindow *window) 
: texture(texture), mouseOver(false), pressed(false)
{
    sprite.setTexture(texture);
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
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (Input::isMouseOver(sprite, window) && pressed)
                pressed = false;
        }
    }
}