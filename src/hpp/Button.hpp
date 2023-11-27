#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "Common.hpp"

class Button
{
public:
    Button();
    Button(sf::Texture &texture);

    void handleInput(sf::Event event);
    void update(sf::RenderWindow *window);
    void render(sf::RenderWindow *window);

    void setOrigin(sf::Vector2f origin);
    void setTexture(sf::Texture &texture);
    void setScale(sf::Vector2f scale);
    void setPosition(sf::Vector2f position);
    void setPressedColor(sf::Color color);

    void setOnAction(const std::function<void()>& callback);

    void setDisabled(bool disabled);
    std::function<void()> getOnAction();

    bool isMouseOver();

    sf::FloatRect getGlobalBounds();
    sf::FloatRect getLocalBounds();

    sf::Vector2f getPosition();

private:
    void init();
    sf::Sprite sprite;
    std::function<void()> onAction;
    bool mouseOver, pressed, disabled;

    sf::Color pressedColor, hoverColor, disabledColor;
};