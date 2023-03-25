#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& window)
{
    myWindow = &window;
    startGame = false;
}

void MenuScreen::initialize() {

    //initializing background imgs and buttons

    //loading Textures aka images
    backIMG.loadFromFile(MENU_BACKGROUND);
    playButtonTexture.loadFromFile(PLAY_BUTTON);
    closeButtonTexture.loadFromFile(CLOSE_BUTTON);

    //setting images for background and buttons
    background.setTexture(&backIMG);
    playButton.setTexture(playButtonTexture);
    closeButton.setTexture(closeButtonTexture);

    //setting background size and position
    background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    background.setPosition(0, 0);


    sf::FloatRect temp;

    // loading font
    font.loadFromFile(FONT_FILEPATH);

    //setting up title font;
    title.setFont(font);
    title.setString("Flappy Bird");
    title.setCharacterSize(SCREEN_WIDTH / 7);
    title.setOutlineColor(sf::Color(45, 119, 8, 255));
    title.setFillColor(sf::Color(246, 239, 215, 255));
    title.setOutlineThickness(8);

    //adjusting origin of title to correctly place it in the middle
    temp = title.getGlobalBounds();
    title.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    title.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 - 10));

    //adjusting origin, scale and details of buttons to correctly place it in proper position etc
    temp = playButton.getGlobalBounds();
    playButton.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    playButton.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, title.getPosition().y + title.getGlobalBounds().height * 2));
    playButton.setScale(0.4, 0.4);

    temp = closeButton.getGlobalBounds();
    closeButton.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    closeButton.setScale(0.3, 0.3);
    closeButton.setPosition(sf::Vector2f(SCREEN_WIDTH - closeButton.getGlobalBounds().width / 1.5, closeButton.getGlobalBounds().height / 2 + 5));


}

bool MenuScreen::isSpritePressed(sf::Sprite sprite, sf::RenderWindow* myWindow)
{
    return sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*myWindow).x, sf::Mouse::getPosition(*myWindow).y);
}

void MenuScreen::gameLoop() {

    while (myWindow->isOpen())
    {
        handleInput();

        update();

        myWindow->clear();

        draw();
    }
}

void MenuScreen::handleInput() {
    sf::Event event;

    while (myWindow->pollEvent(event)) {
        // window closes if close button pressed
        if (event.type == sf::Event::Closed) myWindow->close();

        if (event.type == sf::Event::MouseButtonPressed) {
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                // window closes if close button pressed
                if (isSpritePressed(closeButton, myWindow)) myWindow->close();

                //start Game if play button is pressed
                if (isSpritePressed(playButton, myWindow)) {
                    startGame = true;
                }
                break;
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                // window closes if escape pressed on menu screens
            case sf::Keyboard::Escape:
                myWindow->close();
                break;

                //start Game if Enter or Space is pressed
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

void MenuScreen::update() {
    if (startGame) {
        // starting the GameScreen
        startGame = false;
        GameScreen game(*myWindow);
        game.initialize();
        game.gameLoop();
    }
}

void MenuScreen::draw() {
    myWindow->draw(background);

    myWindow->draw(playButton);
    myWindow->draw(closeButton);

    myWindow->draw(title);

    myWindow->display();
}


