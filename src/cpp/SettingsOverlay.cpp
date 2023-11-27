#include "../hpp/SettingsOverlay.hpp"
#include <iostream>

SettingsOverlay::SettingsOverlay(Game *myGame)
{
    this->game = myGame;
    disabled = true;

    init();
}

void SettingsOverlay::init()
{
    // initializing background

    bgIMG.loadFromFile(SETTINGS_BACKGROUND);
    background.setTexture(&bgIMG);

    background.setSize(sf::Vector2f(game->width * 0.9, game->height * 0.9));
    background.setPosition(game->width * 0.1 / 2, game->height * 0.1 / 2);

    // initializing buttons

    buttonTextures[0].loadFromFile(SETTINGS_CLOSE_BUTTON);
    buttonTextures[1].loadFromFile(SOUND_ON_BUTTON);
    buttonTextures[2].loadFromFile(SOUND_OFF_BUTTON);

    buttons[0].setTexture(buttonTextures[0]);
    buttons[1].setTexture(buttonTextures[1]);

    float scale = (float)game->height / (float)buttons[0].getLocalBounds().height;
    scale /= 12;

    for (int i = 0; i < 2; i++)
        buttons[i].setScale(sf::Vector2f(scale, scale));

    // adjusting origin, scale and details of buttons to correctly place it in proper position etc

    // Close button
    sf::FloatRect temp = buttons[0].getLocalBounds();
    buttons[0].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = background.getLocalBounds();
    buttons[0].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[0].getGlobalBounds().width / 2.0f, temp.top + buttons[0].getGlobalBounds().height * 1.5));

    // Sound button
    temp = buttons[1].getLocalBounds();
    buttons[1].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = background.getLocalBounds();
    buttons[1].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[1].getGlobalBounds().width/2.0f, temp.top + buttons[1].getGlobalBounds().height * 3.5));


    font.loadFromFile(FONT_FILEPATH);

    for (int i = 0;i<1;i++) {
        buttonTexts[i].setFont(font);
        buttonTexts[i].setCharacterSize(game->height / 20);
        sf::FloatRect temp = buttonTexts[i].getLocalBounds();
        buttonTexts[i].setOrigin(temp.left, temp.top + temp.height / 2.0f);
    }

    buttonTexts[0].setString("Sound On/Off");
    buttonTexts[0].setPosition(temp.left + buttonTexts[0].getGlobalBounds().width/2.8f, buttons[1].getPosition().y - buttonTexts[0].getGlobalBounds().height);

    // Close Button Action
    buttons[0].setOnAction([this]()
    {
        disabled = true;
    });
    
    // Sound Button Action
    buttons[1].setOnAction([this]()
    {
        if (sf::Listener::getGlobalVolume() == 0) {
            sf::Listener::setGlobalVolume(50);
            buttons[1].setTexture(buttonTextures[1]);
        }
        else {
            sf::Listener::setGlobalVolume(0);
            buttons[1].setTexture(buttonTextures[2]);
        }
    });
}

void SettingsOverlay::handleInput(sf::Event event)
{

    if (disabled)
        return;

    for (int i = 0; i < 2; i++)
        buttons[i].handleInput(event);
}

void SettingsOverlay::update(const float dt)
{
    if (disabled)
        for (int i = 0; i < 2; i++)
            buttons[i].setDisabled(true);

    else
        for (int i = 0; i < 2; i++)
            buttons[i].setDisabled(false);

    for (int i = 0; i < 2; i++)
        buttons[i].update(game->window);
}

void SettingsOverlay::draw()
{
    if (disabled)
        return;

    sf::RectangleShape darkOverlay;
    darkOverlay.setSize(sf::Vector2f(game->width, game->height));
    darkOverlay.setPosition(0, 0);
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 100));
    game->window->draw(darkOverlay);

    game->window->draw(background);

    for (int i = 0; i < 1; i++)
        game->window->draw(buttonTexts[i]);
    
    for (int i = 0; i < 2; i++)
        buttons[i].render(game->window);
}

void SettingsOverlay::enable()
{
    disabled = false;
}

void SettingsOverlay::disable()
{
    disabled = true;
}

bool SettingsOverlay::isOn()
{
    return !disabled;
}
