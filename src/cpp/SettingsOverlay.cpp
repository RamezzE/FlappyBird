#include "../hpp/SettingsOverlay.hpp"
#include <iostream>

SettingsOverlay::SettingsOverlay(Game *myGame)
{
    this->game = myGame;
    disabled = true;

    // have to be done twice because of a bug
    init();
    init();

    int minWidth = 390;
    int minHeight = 520;

    int num = 3;

    int diffW = game->width - minWidth;
    diffW /= num;

    int diffH = game->height - minHeight;
    diffH /= num;

    int w = game->width;
    int h = game->height;

    screenWidths[3] = w;
    screenHeights[3] = h;

    std::cout << game->width << " " << game->height << std::endl;
    for (int i = 0, j = num - 1; i < num; i++, j--)
    {
        w -= diffW;
        h -= diffH;
        screenWidths[j] = w;
        screenHeights[j] = h;
    }

    bgIMG.loadFromFile(SETTINGS_BACKGROUND);
    background.setTexture(&bgIMG);

    sf::FloatRect temp = buttons[0].getLocalBounds();
    buttons[0].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = buttons[1].getLocalBounds();
    buttons[1].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = buttons[2].getLocalBounds();
    buttons[2].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));
}

static int i = 3;

void SettingsOverlay::init()
{
    // initializing background

    background.setSize(sf::Vector2f(game->width * 0.9, game->height * 0.9));
    background.setPosition(game->width * 0.1 / 2, game->height * 0.1 / 2);

    // initializing buttons

    buttonTextures[0].loadFromFile(SETTINGS_CLOSE_BUTTON);
    buttonTextures[1].loadFromFile(SOUND_ON_BUTTON);
    buttonTextures[2].loadFromFile(SOUND_OFF_BUTTON);
    buttonTextures[3].loadFromFile(NEXT_BUTTON);

    buttons[0].setTexture(buttonTextures[0]);
    buttons[1].setTexture(buttonTextures[1]);
    buttons[2].setTexture(buttonTextures[3]);

    float scale = (float)game->height / (float)buttons[0].getLocalBounds().height;
    scale /= 12;

    for (int i = 0; i < 3; i++)
        buttons[i].setScale(sf::Vector2f(scale, scale));

    // adjusting origin, scale and details of buttons to correctly place it in proper position etc

    // Close button

    sf::FloatRect temp = background.getLocalBounds();
    buttons[0].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[0].getGlobalBounds().width / 2.0f, temp.top + buttons[0].getGlobalBounds().height * 1.5));

    // Sound button

    temp = background.getLocalBounds();
    buttons[1].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[1].getGlobalBounds().width / 2.0f, temp.top + buttons[1].getGlobalBounds().height * 3.5));

    buttons[2].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[2].getGlobalBounds().width / 2.0f, temp.top + buttons[2].getGlobalBounds().height * 5));

    font.loadFromFile(FONT_FILEPATH);

    for (int i = 0; i < 3; i++)
    {
        buttonTexts[i].setFont(font);
        buttonTexts[i].setCharacterSize(game->width / 20);
        sf::FloatRect temp = buttonTexts[i].getLocalBounds();
        buttonTexts[i].setOrigin(temp.left, temp.top + temp.height / 2.0f);
    }

    sf::FloatRect temp2 = buttonTexts[2].getLocalBounds();
    buttonTexts[2].setOrigin(temp2.left + temp2.width / 2.0f, temp2.top + temp2.height / 2.0f);

    buttonTexts[0].setString("Sound On/Off");
    buttonTexts[0].setPosition(temp.left + temp.width / 6, buttons[1].getPosition().y);

    buttonTexts[1].setString("Dimensions");
    buttonTexts[1].setPosition(temp.left + temp.width / 6, buttons[2].getPosition().y);

    buttonTexts[2].setString(std::to_string(game->width) + "x" + std::to_string(game->height));
    buttonTexts[2].setPosition(temp.left + temp.width / 1.45, buttons[2].getPosition().y);

    // Close Button Action
    buttons[0].setOnAction([this]()
                           { 
        if (screenWidths[i] != game->width || screenHeights[i] != game->height)
            resize();
        
        disabled = true; });

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
        } });

    // Next Button Action
    buttons[2].setOnAction([this]
                           {
        // toggle between 4 screen sizes
        
        i++;
        i %= 4;
        buttonTexts[2].setString(std::to_string(screenWidths[i]) + "x" + std::to_string(screenHeights[i])); });
}

void SettingsOverlay::handleInput(sf::Event event)
{
    if (disabled)
        return;

    for (int i = 0; i < 3; i++)
        buttons[i].handleInput(event);
}

void SettingsOverlay::update(const float dt)
{
    if (disabled)
        for (int i = 0; i < 3; i++)
            buttons[i].setDisabled(true);

    else
        for (int i = 0; i < 3; i++)
            buttons[i].setDisabled(false);

    for (int i = 0; i < 3; i++)
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

    for (int i = 0; i < 3; i++)
        game->window->draw(buttonTexts[i]);

    for (int i = 0; i < 3; i++)
        buttons[i].render(game->window);
}

void SettingsOverlay::resize()
{
    game->window->setSize(sf::Vector2u(screenWidths[i], screenHeights[i]));
    game->width = screenWidths[i];
    game->height = screenHeights[i];

    // game->window->setPosition(sf::Vector2i(game->window->getPosition().x, 10));

    sf::FloatRect visibleArea = sf::FloatRect(0, 0, screenWidths[i], screenHeights[i]);
    game->window->setView(sf::View(visibleArea));

    init();
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
