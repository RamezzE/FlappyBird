#include "GameScreen.h"
#include <iostream>

using namespace std;

GameScreen::GameScreen(sf::RenderWindow& window)
{
    myWindow = &window;

    moveUp = collision = died = backToMenu = newHighScore = false;
    focus = pause = true;

    score = 0;

    myObstacle.setGap(myWidth / 3.0f, myPlayer.getHeight() * 2.7f);
    //setting QuadTree boundary to the whole screen
    boundary.setData(0, 0, myWidth, myHeight);

    highScore = 0;
    //gets high score from file
    readHighScore();
    
}

void GameScreen::initialize()
{
    // setting up background imgs
    skyIMG.loadFromFile(SKY_FILEPATH);
    groundIMG.loadFromFile(GROUND_FILEPATH);

    sky.setTexture(&skyIMG);
    ground.setTexture(&groundIMG);

    //setting background size
    sky.setSize(sf::Vector2f(myWidth * 1.5, myHeight));
    ground.setSize(sf::Vector2f(myWidth * 1.5, myHeight));

    //setting buttons textures aka imgs
    retryIMG.loadFromFile(RETRY_BUTTON);
    menuIMG.loadFromFile(MENU_BUTTON);
    pauseIMG.loadFromFile(PAUSE_BUTTON);
    playIMG.loadFromFile(PLAY_BUTTON);

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

        update();

        myWindow->clear();

        draw();
    }
}

void GameScreen::replay()
{
    //resetting everything to the initial values
    myPlayer = Player();
    myObstacle.ObstacleSprites.clear();
    obstaclesFound.clear();

    moveUp = collision = died = backToMenu = newHighScore = false;
    focus = pause = true;

    score = 0;
    scoreText.setString("Score: " + to_string(score));

    flashCLK.restart();
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
            if (score > highScore) {
                highScore = score;
                saveHighScore();
            }
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
                }
                if (died || pause) { // only detect clicks on restart and menu buttons if game is paused or player died
                    if (MenuScreen::isSpritePressed(retryButton, myWindow)) {
                        replay();
                        break;
                    }
                    else if (MenuScreen::isSpritePressed(menuButton, myWindow)) {
                        backToMenu = true;
                        if (score > highScore) {
                            highScore = score;
                            saveHighScore();
                        }
                        break;
                    }
                }

                // normal left click lets moveUp = true
                moveUp = true;
                jumpCLK.restart();
                pause = false;
                break;
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Space:

                // move up if space is pressed
                moveUp = true;
                pause = false;
                if (died) {
                    replay();
                }
                break;
            case sf::Keyboard::Escape:

                //toggle between pause and play states
                if (pause) pause = false;
                else pause = true;
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                //returns to menu if pressed Escape after player died
                if (died) backToMenu = true;
                break;
            }
        }
    }
}

void GameScreen::update()
{

    if (!pause || died || collision) {
        //pause Button displays pauseIMG if game is running normally
        pauseButton.setTexture(pauseIMG);
        pause = false;
    }
    else pauseButton.setTexture(playIMG);

    // moves player, object and background if no collisions && window is focused && game is not paused
    if (!collision && focus) {
        myPlayer.animate(dt);   //animating player and moves obstacles if game is not paused
        if (!pause) {
            myObstacle.moveObstacles(myTree, dt, myPlayer, score);
            myObstacle.spawnObstacle();

            if (moveUp) {
                if (!myPlayer.jump(jumpCLK, dt)) {
                    moveUp = false;
                }
            }
            else {
                myPlayer.fall(dt);
            }
        }
    }


    float x1, x2, y1, y2;
    x1 = myPlayer.getX();
    y1 = myPlayer.getY();
    x2 = x1 + myPlayer.getWidth();
    y2 = y1 + myPlayer.getHeight();

    //sets rectangle around the player boundaries to detect for collisions
    playerRect.setData(x1, y1 * 1.05, x2 * 0.6, y2 * 0.8);

    //queries the tree if any objects are found. If any are found they are stored in the obstaclesFound vector
    myTree.query(playerRect, obstaclesFound);

    //if obstaclesFound vector has size > 0, it means an object is detected so player loses

    if (obstaclesFound.size() > 0 && !collision) { //player lost
        myPlayer.setVelocity(0, 0);
        collision = true; //collision detected
        initializeTree();
        obstaclesFound.clear(); //reseting vector
        flashCLK.restart(); // quick flash display when player loses
    }

    if (collision && !died) { //player dying animation
        if (myPlayer.die(dt, playerRect, myTree)) died = true; //died = true when player eventually hits the ground
    }

    //saves new high score when player dies if score > high score
    if (score > highScore && died) {
        highScore = score;
        newHighScore = true;
        saveHighScore();
    }

    //display text if new high score is detected
    if (newHighScore) {
        scoreText.setString("Bravo!!");
    }
    else {
        scoreText.setString("Score: " + to_string(score));
    }

    //high score normal text
    highScoreText.setString("High Score: " + to_string(highScore));

}

void GameScreen::draw()
{
    myWindow->draw(sky);
    myObstacle.drawObstacles(myWindow);

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
    
   /* sf::RectangleShape myRectangle;
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
    myRectangle.setRotation(myPlayer.getRotation());

    myWindow->draw(myRectangle2);*/
    
    myWindow->display();
}

void GameScreen::initializeTree()
{
    myTree = QuadTree(boundary, 1);
    myTree.insert(myObstacle.spawnGround()); //insert ground every frame

    if (collision) return; // if collision is detected, no obstacles are inserted into the tree

    for (int i = 0; i < myObstacle.ObstacleSprites.size(); i++) {
        //inserting objects in the tree
        myTree.insert(myObstacle.ObstacleSprites[i]);
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

void GameScreen::saveHighScore()
{
    //saves high Score into binary file
    ofstream fileWrite(HIGH_SCORE_FILEPATH, ios::out | ios::binary);
    fileWrite.write((char*)&highScore, sizeof(highScore));
    fileWrite.close();

}

void GameScreen::readHighScore()
{
    //reads high score from binary file and saves it into highScore variable
    ifstream fileRead(HIGH_SCORE_FILEPATH, ios::in | ios::binary);
    fileRead.read((char*)&highScore, sizeof(highScore));
    fileRead.close();

}








