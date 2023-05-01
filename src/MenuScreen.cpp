#include "MenuScreen.hpp"

MenuScreen::MenuScreen(Game *myGame)
{
    this->game = myGame;
    startGame = false;

    init();
}

void MenuScreen::init()
{

    // initializing background imgs and buttons

    Collision::CreateTextureAndBitmask(bgIMG, MENU_BACKGROUND);
    Collision::CreateTextureAndBitmask(buttonTextures[0], PLAY_BUTTON);
    Collision::CreateTextureAndBitmask(buttonTextures[1], CLOSE_BUTTON);
    Collision::CreateTextureAndBitmask(buttonTextures[2], SETTINGS_BUTTON);

    // setting images for background and buttons
    background.setTexture(&bgIMG);

    for (int i = 0; i < 3; i++)
        buttons[i].setTexture(buttonTextures[i]);

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
    buttons[0].setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    buttons[0].setPosition(sf::Vector2f(game->width / 2.0f, title.getPosition().y + title.getGlobalBounds().height * 2.0f));

    float scale = (float)game->height / (float)buttons[0].getLocalBounds().height;
    scale /= 10;
    buttons[0].setScale(scale, scale);

    // close button
    buttons[1].setScale(scale, scale);
    buttons[1].setPosition(sf::Vector2f(game->width - (buttons[1].getGlobalBounds().width + game->width * 0.005f), game->height * 0.005f));

    // settings button
    buttons[2].setScale(scale, scale);
    buttons[2].setPosition(sf::Vector2f(game->width - (buttons[2].getGlobalBounds().width + +buttons[1].getGlobalBounds().width + game->width * 2 * 0.005f), game->height * 0.005f));
}



void MenuScreen::handleInput()
{
    sf::Event event;

    while (game->window->pollEvent(event))
    {
        // window closes if close button pressed
        if (event.type == sf::Event::Closed)
            game->window->close();

        if (event.type == sf::Event::MouseButtonReleased)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                if (Input::isMouseOver(buttons[0], game->window))
                    startGame = true;
                else if (Input::isMouseOver(buttons[1], game->window))
                    game->window->close();       

                break;
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                game->window->close();
                break;
            case sf::Keyboard::Enter:
                startGame = true;
                break;
            case sf::Keyboard::Space:
                startGame = true;
                break;
            }
        }
    }
}

void MenuScreen::update(const float dt)
{
    if (startGame)
    {
        game->changeScreen(new GameScreen(game));
        startGame = false;
    }
}

void MenuScreen::draw()
{
    game->window->draw(background);

    for (int i = 0; i < 3; i++)
        game->window->draw(buttons[i]);

    game->window->draw(title);
}
