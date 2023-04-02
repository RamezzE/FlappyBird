#include "MenuScreen.hpp"

MenuScreen::MenuScreen(sf::RenderWindow& window)
{
    myWindow = &window;
    startGame = false;
}

void MenuScreen::initialize() {

    //initializing background imgs and buttons

    Collision::CreateTextureAndBitmask(backIMG, MENU_BACKGROUND);
    Collision::CreateTextureAndBitmask(playButtonTexture, PLAY_BUTTON);
    Collision::CreateTextureAndBitmask(closeButtonTexture, CLOSE_BUTTON);

    //setting images for background and buttons
    background.setTexture(&backIMG);
    playButton.setTexture(playButtonTexture);
    closeButton.setTexture(closeButtonTexture);

    //setting background size and position
    background.setSize(sf::Vector2f(myWidth, myHeight));
    background.setPosition(0, 0);


    sf::FloatRect temp;

    // loading font
    font.loadFromFile(FONT_FILEPATH);

    //setting up title font;
    title.setFont(font);
    title.setString("FlarKy Bird");
    title.setCharacterSize(myWidth / 8);
    title.setOutlineThickness(title.getCharacterSize() / 8);

    title.setOutlineColor(sf::Color(45, 119, 8, 255));
    title.setFillColor(sf::Color(246, 239, 215, 255));

    //adjusting origin of title to correctly place it in the middle
    temp = title.getLocalBounds();
    title.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    title.setPosition(sf::Vector2f(myWidth / 2.0f, myHeight / 4 - 10));

    //adjusting origin, scale and details of buttons to correctly place it in proper position etc
    temp = playButton.getLocalBounds();
    playButton.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    playButton.setPosition(sf::Vector2f(myWidth / 2.0f, title.getPosition().y + title.getGlobalBounds().height * 2.0f));
    float num = (float)myHeight / (float)playButton.getLocalBounds().height;
    num /= 10;
    playButton.setScale(num, num);
    closeButton.setScale(num, num);

    temp = closeButton.getGlobalBounds();
    //closeButton.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    //closeButton.setOrigin(temp.left,temp.top);

    closeButton.setPosition(sf::Vector2f(myWidth - (closeButton.getGlobalBounds().width + myWidth*0.005f), myHeight * 0.005f));
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


