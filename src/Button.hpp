#pragma once
#include <SFML/Graphics.hpp>
#include "Common.hpp"


class Button
{
public:
    Button(sf::Texture &texture, sf::RenderWindow *window);

    void handleInput(sf::Event event);
    void update();
    void draw();

    bool isPressed() const;

    sf::Vector2f getGlobalBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture &texture;
    bool mouseOver, pressed;

    sf::RenderWindow *window;

};