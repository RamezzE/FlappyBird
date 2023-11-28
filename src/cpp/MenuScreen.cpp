#include "../hpp/MenuScreen.hpp"

MenuScreen::MenuScreen(Game *myGame)
: settings(myGame)
{
    this->game = myGame;
    init();
}

void MenuScreen::init()
{
    // initializing background imgs and buttons
    
    bgIMG.loadFromFile(MENU_BACKGROUND);
    buttonTextures[0].loadFromFile(PLAY_BUTTON);
    buttonTextures[1].loadFromFile(CLOSE_BUTTON);
    buttonTextures[2].loadFromFile(SETTINGS_BUTTON);

    // setting images for background and buttons
    background.setTexture(&bgIMG);

    for (int i = 0; i < 3; i++)
        buttons[i].setTexture(buttonTextures[i]);

    float scale = (float)game->height / (float)buttons[0].getLocalBounds().height;
    scale /= 10;

    for (int i = 0; i < 3; i++)
        buttons[i].setScale(sf::Vector2f(scale, scale));

    // setting background size and position
    background.setSize(sf::Vector2f(game->width, game->height));
    background.setPosition(0, 0);

    sf::FloatRect temp;

    // loading font
    font.loadFromFile(FONT_FILEPATH);

    // setting up title font;
    title.setFont(font);
    title.setString("FlarKy Bird");
    title.setCharacterSize(game->height / 9);
    title.setOutlineThickness(title.getCharacterSize() / 9);

    title.setOutlineColor(sf::Color(45, 119, 8, 255));
    title.setFillColor(sf::Color(246, 239, 215, 255));

    // adjusting origin of title to correctly place it in the middle
    temp = title.getLocalBounds();
    title.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    title.setPosition(sf::Vector2f(game->width / 2.0f, game->height / 4 - 10));

    // adjusting origin, scale and details of buttons to correctly place it in proper position etc

    // play button
    temp = buttons[0].getLocalBounds();
    buttons[0].setOrigin(sf::Vector2f(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f));
    buttons[0].setPosition(sf::Vector2f(game->width / 2.0f, title.getPosition().y + title.getGlobalBounds().height * 2.0f));

    // close button
    buttons[1].setPosition(sf::Vector2f(game->width - (buttons[1].getGlobalBounds().width + game->width * 0.005f), game->height * 0.005f));

    // settings button
    buttons[2].setPosition(sf::Vector2f(game->width - (buttons[2].getGlobalBounds().width + +buttons[1].getGlobalBounds().width + game->width * 2 * 0.005f), game->height * 0.005f));


    // setting up onAction for buttons
    buttons[0].setOnAction([game = this->game]() {
        game->changeScreen(ScreenType::Gameplay);
    });

    buttons[1].setOnAction([game = this->game]() {
        game->window->close();
    });

    buttons[2].setOnAction([this]() {
        settings.enable();
    });

}

void MenuScreen::handleInput()
{
    sf::Event event;

    while (game->window->pollEvent(event))
    {
        for (ushort i = 0; i < 3; i++)
            buttons[i].handleInput(event);

        settings.handleInput(event);
        
        // window closes if close button pressed
        if (event.type == sf::Event::Closed)
            game->window->close();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                if (settings.isOn())
                    settings.disable();
                else
                    game->window->close();
                break;
            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                game->changeScreen(ScreenType::Gameplay);
                break;
            }
        }
    }
}

void MenuScreen::update(const float dt)
{
    if (background.getSize().x != game->width || background.getSize().y != game->height)
        init();
        
    settings.update(dt);
    if (settings.isOn()) 
        for (ushort i = 0; i < 3; i++)
            buttons[i].setDisabled(true);

    else 
        for (ushort i = 0; i < 3; i++)
            buttons[i].setDisabled(false);
    
    
    for (ushort i = 0; i < 3; i++)
        buttons[i].update(game->window);
}

void MenuScreen::draw()
{
    game->window->draw(background);

    for (int i = 0; i < 3; i++)
        buttons[i].render(game->window);

    game->window->draw(title);

    settings.draw();
}
