#include "GameScreen.hpp"
#include <iostream>

GameScreen::GameScreen(sf::RenderWindow& window)
    :myObstacle(Obstacle(myPlayer))
{
    myWindow = &window;
    myObstacle.setGap(myPlayer.getHeight() * 2.7f);

    //setting QuadTree boundary to the whole screen
    boundary.setData(0, 0, myWidth, myHeight);

    init();
    newGame();
    
}

void GameScreen::init()
{
    // setting up background imgs
    Collision::CreateTextureAndBitmask(skyIMG, SKY_FILEPATH);
    Collision::CreateTextureAndBitmask(groundIMG, GROUND_FILEPATH);

    sky.setTexture(&skyIMG);
    ground.setTexture(&groundIMG);

    //setting background size
    sky.setSize(sf::Vector2f(myWidth * 1.5, myHeight));
    ground.setSize(sf::Vector2f(myWidth * 1.5, myHeight));

    //setting buttons textures aka imgs
    Collision::CreateTextureAndBitmask(retryIMG, RETRY_BUTTON);
    Collision::CreateTextureAndBitmask(menuIMG, MENU_BUTTON);
    Collision::CreateTextureAndBitmask(pauseIMG, PAUSE_BUTTON);
    Collision::CreateTextureAndBitmask(playIMG, PLAY_BUTTON);

    //setting buttons textures, size, scale, position etc
    retryButton.setTexture(retryIMG);
    menuButton.setTexture(menuIMG);
    pauseButton.setTexture(pauseIMG);

    float num = (float)myHeight / (float)menuButton.getLocalBounds().height;
    num /= 10;
    retryButton.setScale(num, num);
    menuButton.setScale(num, num);
    pauseButton.setScale(num, num);

    menuButton.setPosition(sf::Vector2f(myWidth - (pauseButton.getGlobalBounds().width*3 + myWidth * 0.005f*3), myHeight * 0.005f));
    retryButton.setPosition(sf::Vector2f(myWidth - (pauseButton.getGlobalBounds().width*2 + myWidth * 0.005f*2), myHeight * 0.005f));
    pauseButton.setPosition(sf::Vector2f(myWidth - (pauseButton.getGlobalBounds().width + myWidth * 0.005f), myHeight * 0.005f));

    //loading font and setting up score and highscore text
    font.loadFromFile(FONT_FILEPATH);
    scoreText.setString("Score: 000");
    scoreText.setFont(font);
    scoreText.setCharacterSize(myHeight / 20);

    sf::FloatRect temp = highScoreText.getGlobalBounds();
    highScoreText.setString("High Score: 000");
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(myHeight / 20);
    highScoreText.setPosition(sf::Vector2f(myWidth-highScoreText.getGlobalBounds().width, myHeight-highScoreText.getGlobalBounds().height*2));
    
    scoreText.setPosition(sf::Vector2f(myWidth-highScoreText.getGlobalBounds().width, myHeight-highScoreText.getGlobalBounds().height*3.5));

    highScoreText.setString("High Score: " + std::to_string(myPlayer.highScore));
}

void GameScreen::newGame()
{
    collision = died = backToMenu = newHighScore = false;
    focus = pause = true;
    obstaclesFound.clear();

    scoreText.setString("Score: " + std::to_string(myPlayer.score));

    flashCLK.restart();
}

void GameScreen::replay()
{
    //resetting everything to the initial values
    newGame();
    myPlayer.newGame();
    myObstacle.newGame();

}

void GameScreen::gameLoop()
{
    sf::Clock clk;
    while (myWindow->isOpen())
    {
        //calculating delta time aka time for one frame. (To make frame rate independent gameplay) 
        dt = clk.restart().asSeconds();

        handleInput();

        if (backToMenu) {
            // breaks the loop to return back to Menu, resets the variable to false;
            backToMenu = false;
            break;
        }

        update(dt);

        myWindow->clear();

        draw();
    }
}


void GameScreen::handleInput()
{
    // quad Tree is reconstructed every frame, so it is reinitialized every frame
    initializeTree();

    sf::Event event;

    while (myWindow->pollEvent(event))
    {
        // if screen is the one in focus
        if (event.type == sf::Event::GainedFocus)  focus = true;

        // if screen is not in focus 
        if (event.type == sf::Event::LostFocus)  focus = false;

        //saves score before closing window
        if (event.type == sf::Event::Closed) {
            myPlayer.saveHighScore();
            myWindow->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                if (MenuScreen::isSpritePressed(pauseButton, myWindow)) {
                    //toggle between play and pause states if pause button is pressed
                    if (pause) pause = false;
                    else {
                        pause = true;
                        break;
                    }
                    break;
                }
                if (died || pause) { // only detect clicks on restart and menu buttons if game is paused or player died
                    if (MenuScreen::isSpritePressed(retryButton, myWindow)) {
                        replay();
                        break;
                    }
                    else if (MenuScreen::isSpritePressed(menuButton, myWindow)) {
                        backToMenu = true;
                        myPlayer.saveHighScore();
                        break;
                    }
                }

                // normal left click lets moveUp = true
                myPlayer.tap();
                pause = false;
                break;
            }
        }

        if (event.type == sf::Event::KeyPressed) { ///////////////////////////BUG here
            switch (event.key.code) {
            case sf::Keyboard::Space:
                // move up if space is pressed
                if (died)
                    replay();
                else {
                    myPlayer.tap();
                    pause = false;
                }
                break;
            case sf::Keyboard::Escape:
                //toggle between pause and play states
                if (pause) 
                    pause = false;
                else 
                    pause = true;
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                //returns to menu if pressed Escape after player died
                if (died) 
                    backToMenu = true;
                break;
            }
        }
    }
}

void GameScreen::update(float dt)
{   
    if (!pause || died || collision) {
        //pause Button displays pauseIMG if game is running normally
        pauseButton.setTexture(pauseIMG);
        pause = false;
    }
    else pauseButton.setTexture(playIMG);

    // moves player, object and background if no collisions && window is focused && game is not paused
    if (!collision && focus) {   
        myPlayer.animate(dt); //animating player and moves obstacles if game is not paused
        if (!pause) {
            myPlayer.update(dt);
            myObstacle.update(dt);
        }
    }
    
    if (pause || !focus)
        return;
    float x1, x2, y1, y2;
    x1 = myPlayer.getX();
    y1 = myPlayer.getY();
    x2 = x1 + myPlayer.getWidth();
    y2 = y1 + myPlayer.getHeight();

    //sets rectangle around the player boundaries to detect for collisions

    //queries the tree if any objects are found. If any are found they are stored in the obstaclesFound vector
    myTree.query(myPlayer.getSprite(), obstaclesFound);

    //if obstaclesFound vector has size > 0, it means an object is detected so player loses

    if (obstaclesFound.size() > 0 && !collision) { //player lost
        myPlayer.setVelocity(0, 0);
        collision = true; //collision detected
        initializeTree();
        obstaclesFound.clear(); //reseting vector
        flashCLK.restart(); // quick flash display when player loses
    }

    if (collision && !died) { //player dying animation
        if (myPlayer.die(dt, myTree)) 
            died = true; //died = true when player eventually hits the ground
    }

    //saves new high score when player dies if score > high score
    if (myPlayer.score > myPlayer.highScore && died) {
        newHighScore = true;
        myPlayer.saveHighScore();
    }

    //display text if new high score is detected
    if (newHighScore) {
        scoreText.setString("Bravo!!");
        highScoreText.setString("High Score: " + std::to_string(myPlayer.highScore));
    }
    else {
        scoreText.setString("Score: " + std::to_string(myPlayer.score));
    }
}

void GameScreen::draw()
{
    myWindow->draw(sky);
    myObstacle.draw(myWindow);

    myWindow->draw(ground);
    myWindow->draw(scoreText);
    myWindow->draw(highScoreText);
    myWindow->draw(pauseButton);
    myPlayer.draw(myWindow);

    flashScreen();

    if (died || pause) { //display buttons if game is paused or player loses
        myWindow->draw(retryButton);
        myWindow->draw(menuButton);
    }
    
    /*sf::RectangleShape myRectangle;
    myRectangle.setFillColor(sf::Color(255, 255, 255,150));
    myRectangle.setSize(sf::Vector2f(myWidth, myHeight*0.5f-myHeight*0.1f));
    myRectangle.setPosition(0, myHeight*0.1f);
    myWindow->draw(myRectangle);

    sf::RectangleShape myRectangle2;
    myRectangle2.setFillColor(sf::Color(24, 251, 255, 150));
    myRectangle2.setSize(sf::Vector2f(myPlayer.getWidth(),myPlayer.getHeight()));
    sf::FloatRect bounds = myRectangle2.getLocalBounds();
    myRectangle2.setOrigin(bounds.left+bounds.width /2.0f, bounds.top + bounds.height /2.0f );
    myRectangle2.setPosition(myPlayer.getX(),myPlayer.getY());

    myWindow->draw(myRectangle2);*/
    
    myWindow->display();
}

void GameScreen::initializeTree()
{
    myTree = QuadTree(boundary, 1);
    myTree.insert(myObstacle.spawnGround()); //insert ground every frame

    if (collision) return; // if collision is detected, no obstacles are inserted into the tree
    
    std::deque<sf::Sprite> obstacles = myObstacle.getSprites();

    for (int i = 0; i < obstacles.size(); i++) {
        //inserting objects in the tree
        myTree.insert(obstacles[i]);
    }
}



void GameScreen::flashScreen()
{
    //displays quick flash (white square) for a few milliseconds when dying or at restarting the game
    if (flashCLK.getElapsedTime().asSeconds() < FLASH_TIME) {

        sf::RectangleShape white(sf::Vector2f(myWidth, myHeight));

        white.setFillColor(sf::Color(255, 255, 255, 100));

        myWindow->draw(white);
    }
}








