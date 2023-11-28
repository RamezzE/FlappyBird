#include "../hpp/SettingsOverlay.hpp"
#include <iostream>

static int screenIndex = 3;
static int difficultyIndex = 0;

SettingsOverlay::SettingsOverlay(Game *myGame)
{
    this->game = myGame;
    disabled = true;

    difficulties[0] = "Normal";
    difficulties[1] = "Hard";
    difficulties[2] = "Extreme";

    buttonTextures[0].loadFromFile(SETTINGS_CLOSE_BUTTON);
    buttonTextures[1].loadFromFile(SOUND_ON_BUTTON);
    buttonTextures[2].loadFromFile(SOUND_OFF_BUTTON);
    buttonTextures[3].loadFromFile(NEXT_BUTTON);

    buttons[0].setTexture(buttonTextures[0]);
    buttons[1].setTexture(buttonTextures[1]);
    buttons[2].setTexture(buttonTextures[3]);
    buttons[3].setTexture(buttonTextures[3]);

    // have to be done twice because of a bug
    init();
    init();

    initScreenDimensions();

    bgIMG.loadFromFile(SETTINGS_BACKGROUND);
    background.setTexture(&bgIMG);

    tableIMG.loadFromFile(SETTINGS_TABLE);
    table.setTexture(&tableIMG);

    sf::FloatRect temp = buttons[0].getLocalBounds();
    buttons[0].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = buttons[1].getLocalBounds();
    buttons[1].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = buttons[2].getLocalBounds();
    buttons[2].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    temp = buttons[3].getLocalBounds();
    buttons[3].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));

    // Close Button Action
    buttons[0].setOnAction([this]()
                           { 
        if (screenWidths[screenIndex] != game->width || screenHeights[screenIndex] != game->height)
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

    // Dimensions Button Action
    buttons[2].setOnAction([this]
                           {
        // toggle between 4 screen sizes
        
        screenIndex++;
        screenIndex %= 4;
        buttonTexts[2].setString(std::to_string(screenWidths[screenIndex]) + "x" + std::to_string(screenHeights[screenIndex])); });

    // Difficulty Button Action
    buttons[3].setOnAction([this]
                           {
        // toggle between 3 difficulties
        difficultyIndex++;
        difficultyIndex %= 3;
        
        buttonTexts[4].setString(difficulties[difficultyIndex]);

        Difficulty difficulty;
        switch (difficultyIndex)
        {
        case 1:
            difficulty = Difficulty::Hard;
            break;
        case 2:
            difficulty = Difficulty::Extreme;
            break;
        default:
            difficulty = Difficulty::Normal;
            break;
        }

        game->setDifficulty(difficulty); });
}

void SettingsOverlay::initScreenDimensions()
{
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

    for (int i = 0, j = num - 1; i < num; i++, j--)
    {
        w -= diffW;
        h -= diffH;
        screenWidths[j] = w;
        screenHeights[j] = h;
    }
}

void SettingsOverlay::init()
{
    // initializing background

    background.setSize(sf::Vector2f(game->width * 0.9, game->height * 0.9));
    background.setPosition(game->width * 0.1 / 2, game->height * 0.1 / 2);

    table.setSize(sf::Vector2f(game->width * 0.8, game->height * 0.65));
    table.setPosition(game->width * 0.115, game->height * 0.2);

    // scaling buttons

    float scale = (float)game->height / (float)buttons[0].getLocalBounds().height;
    scale /= 12;

    for (int i = 0; i < 4; i++)
        buttons[i].setScale(sf::Vector2f(scale, scale));

    // adjusting origin, scale and details of buttons to correctly place it in proper position etc

    // Close button

    sf::FloatRect temp = background.getLocalBounds();
    buttons[0].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[0].getGlobalBounds().width / 2.0f, temp.top + buttons[0].getGlobalBounds().height * 1.75));

    // Sound button

    temp = background.getLocalBounds();
    buttons[1].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[1].getGlobalBounds().width * 1.25, temp.top + buttons[1].getGlobalBounds().height * 3.5));

    buttons[2].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[2].getGlobalBounds().width * 1.25, temp.top + buttons[2].getGlobalBounds().height * 5));

    buttons[3].setPosition(sf::Vector2f((temp.left + temp.width) - buttons[3].getGlobalBounds().width * 1.25, temp.top + buttons[3].getGlobalBounds().height * 6.5));

    font.loadFromFile(FONT_FILEPATH);

    for (int i = 0; i < 5; i++)
    {
        buttonTexts[i].setFont(font);
        buttonTexts[i].setCharacterSize(game->width / 20);
        sf::FloatRect temp = buttonTexts[i].getLocalBounds();
        buttonTexts[i].setOrigin(temp.left, temp.top + temp.height / 2.0f);
        buttonTexts[i].setFillColor(sf::Color::Black);
    }

    sf::FloatRect temp2 = buttonTexts[2].getLocalBounds();
    buttonTexts[2].setOrigin(temp2.left, temp2.top + temp2.height / 2.0f);

    temp2 = buttonTexts[4].getLocalBounds();
    buttonTexts[4].setOrigin(temp2.left, temp2.top + temp2.height / 2.0f);

    buttonTexts[0].setString("Sound");
    buttonTexts[0].setPosition(temp.left + temp.width / 4.5, buttons[1].getPosition().y);

    buttonTexts[1].setString("Dimensions");
    buttonTexts[1].setPosition(temp.left + temp.width / 4.5, buttons[2].getPosition().y);

    buttonTexts[2].setString(std::to_string(game->width) + "x" + std::to_string(game->height));
    buttonTexts[2].setPosition(buttonTexts[1].getPosition().x + buttonTexts[1].getGlobalBounds().width + game->width * 0.05, buttons[2].getPosition().y);

    buttonTexts[3].setString("Difficulty");
    buttonTexts[3].setPosition(temp.left + temp.width / 4.5, buttons[3].getPosition().y);

    buttonTexts[4].setString(difficulties[difficultyIndex]);
    buttonTexts[4].setPosition(buttonTexts[3].getPosition().x + buttonTexts[3].getGlobalBounds().width + game->width * 0.05, buttons[3].getPosition().y);

    for (int i = 0; i < 6; i++)
    {
        sf::FloatRect temp = controlsText[i].getLocalBounds();
        controlsText[i].setOrigin(sf::Vector2f(temp.left, temp.top + temp.height / 2.0f));
        controlsText[i].setFont(font);
        controlsText[i].setCharacterSize(game->width / 30);
        controlsText[i].setFillColor(sf::Color::Black);
    }

    controlsText[0].setString("Space or Left Click");
    controlsText[1].setString("Jump");

    controlsText[2].setString("R");
    controlsText[3].setString("Restart");

    controlsText[4].setString("Esc");
    controlsText[5].setString("Pause or Exit");

    controlsText[0].setPosition(buttonTexts[0].getPosition().x, temp.top + buttons[3].getGlobalBounds().height * 8);
    controlsText[1].setPosition(buttonTexts[0].getPosition().x + game->width * 0.4f, temp.top + buttons[3].getGlobalBounds().height * 8);

    controlsText[2].setPosition(buttonTexts[0].getPosition().x, temp.top + buttons[3].getGlobalBounds().height * 8.5);
    controlsText[3].setPosition(buttonTexts[0].getPosition().x + game->width * 0.4f, temp.top + buttons[3].getGlobalBounds().height * 8.5);

    controlsText[4].setPosition(buttonTexts[0].getPosition().x, temp.top + buttons[3].getGlobalBounds().height * 9);
    controlsText[5].setPosition(buttonTexts[0].getPosition().x + game->width * 0.4f, temp.top + buttons[3].getGlobalBounds().height * 9);
}

void SettingsOverlay::handleInput(sf::Event event)
{
    if (disabled)
        return;

    for (int i = 0; i < 4; i++)
        buttons[i].handleInput(event);
}

void SettingsOverlay::update(const float dt)
{
    if (disabled)
        for (int i = 0; i < 4; i++)
            buttons[i].setDisabled(true);

    else
        for (int i = 0; i < 4; i++)
            buttons[i].setDisabled(false);

    for (int i = 0; i < 4; i++)
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
    game->window->draw(table);

    for (int i = 0; i < 5; i++)
        game->window->draw(buttonTexts[i]);

    for (int i = 0; i < 4; i++)
        buttons[i].render(game->window);

    for (int i = 0; i < 6; i++)
        game->window->draw(controlsText[i]);
}

void SettingsOverlay::resize()
{
    game->window->setSize(sf::Vector2u(screenWidths[screenIndex], screenHeights[screenIndex]));
    game->width = screenWidths[screenIndex];
    game->height = screenHeights[screenIndex];

    sf::FloatRect visibleArea = sf::FloatRect(0, 0, screenWidths[screenIndex], screenHeights[screenIndex]);
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
