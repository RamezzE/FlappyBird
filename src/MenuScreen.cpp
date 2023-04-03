#include "MenuScreen.hpp"

MenuScreen::MenuScreen(Game* myGame)
{
    this->game = myGame;
    startGame = false;

    init();
}

void MenuScreen::init() {

    //initializing background imgs and buttons

    Collision::CreateTextureAndBitmask(bgIMG, MENU_BACKGROUND);
    Collision::CreateTextureAndBitmask(playButtonTexture, PLAY_BUTTON);
    Collision::CreateTextureAndBitmask(closeButtonTexture, CLOSE_BUTTON);

    //setting images for background and buttons
    background.setTexture(&bgIMG);
    playButton.setTexture(playButtonTexture);
    closeButton.setTexture(closeButtonTexture);

    //setting background size and position
    background.setSize(sf::Vector2f(game->width, game->height));
    background.setPosition(0, 0);

    sf::FloatRect temp;

    // loading font
    font.loadFromFile(FONT_FILEPATH);

    //setting up title font;
    title.setFont(font);
    title.setString("FlarKy Bird");
    title.setCharacterSize(game->height / 9);
    title.setOutlineThickness(title.getCharacterSize() / 9);

    title.setOutlineColor(sf::Color(45, 119, 8, 255));
    title.setFillColor(sf::Color(246, 239, 215, 255));

    //adjusting origin of title to correctly place it in the middle
    temp = title.getLocalBounds();
    title.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    title.setPosition(sf::Vector2f(game->width / 2.0f, game->height / 4 - 10));

    //adjusting origin, scale and details of buttons to correctly place it in proper position etc
    temp = playButton.getLocalBounds();
    playButton.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    playButton.setPosition(sf::Vector2f(game->width / 2.0f, title.getPosition().y + title.getGlobalBounds().height * 2.0f));
    float scale = (float)game->height / (float)playButton.getLocalBounds().height;
    scale /= 10;
    playButton.setScale(scale, scale);
    closeButton.setScale(scale, scale);

    closeButton.setPosition(sf::Vector2f(game->width - (closeButton.getGlobalBounds().width + game->width*0.005f), game->height * 0.005f));
}

bool MenuScreen::isSpritePressed(sf::Sprite sprite, sf::RenderWindow* myWindow)
{
    return sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*myWindow).x, sf::Mouse::getPosition(*myWindow).y);
}


void MenuScreen::handleInput() {
    sf::Event event;

    while (game->window->pollEvent(event)) {
        // window closes if close button pressed
        if (event.type == sf::Event::Closed) 
            game->window->close();

        if (event.type == sf::Event::MouseButtonPressed) {
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                if (isSpritePressed(closeButton, game->window)) 
                    game->window->close();
                else if (isSpritePressed(playButton, game->window))
                    startGame = true;
                break;
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
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

void MenuScreen::update(const float dt) {
    if (startGame) {
        game->changeScreen(new GameScreen(game));
        startGame = false;
    }
}

void MenuScreen::draw() {
    game->window->draw(background);

    game->window->draw(playButton);
    game->window->draw(closeButton);

    game->window->draw(title);
}


