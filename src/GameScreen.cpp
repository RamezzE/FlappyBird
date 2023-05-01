#include "GameScreen.hpp"
#include <iostream>

GameScreen::GameScreen(Game *myGame)
    : ObstacleSpawner(Obstacle(&player, &myTree)),
      player(Player(&myTree))
{
    this->game = myGame;
    ObstacleSpawner.setGap(player.getHeight() * 2.7f);

    // setting QuadTree boundary to the whole screen
    boundary = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(game->width, game->height));
    myTree = QuadTree<sf::Sprite>(boundary, 1);
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

    // setting background size
    sky.setSize(sf::Vector2f(game->width * 1.5, game->height));
    ground.setSize(sf::Vector2f(game->width * 1.5, game->height));

    // setting buttons textures aka imgs
    Collision::CreateTextureAndBitmask(retryIMG, RETRY_BUTTON);
    Collision::CreateTextureAndBitmask(menuIMG, MENU_BUTTON);
    Collision::CreateTextureAndBitmask(pauseIMG, PAUSE_BUTTON);
    Collision::CreateTextureAndBitmask(playIMG, PLAY_BUTTON);

    // setting buttons textures, size, scale, position etc
    retryButton.setTexture(retryIMG);
    menuButton.setTexture(menuIMG);
    pauseButton.setTexture(pauseIMG);

    float scale = (float)game->height / (float)menuButton.getLocalBounds().height;
    scale /= 10;
    retryButton.setScale(scale, scale);
    menuButton.setScale(scale, scale);
    pauseButton.setScale(scale, scale);

    menuButton.setPosition(sf::Vector2f(game->width - (pauseButton.getGlobalBounds().width * 3 + game->width * 0.005f * 3), game->height * 0.005f));
    retryButton.setPosition(sf::Vector2f(game->width - (pauseButton.getGlobalBounds().width * 2 + game->width * 0.005f * 2), game->height * 0.005f));
    pauseButton.setPosition(sf::Vector2f(game->width - (pauseButton.getGlobalBounds().width + game->width * 0.005f), game->height * 0.005f));

    // loading font and setting up score and highscore text
    font.loadFromFile(FONT_FILEPATH);
    scoreText.setString("Score: 000");
    scoreText.setFont(font);
    scoreText.setCharacterSize(game->height / 20);

    sf::FloatRect temp = highScoreText.getGlobalBounds();
    highScoreText.setString("High Score: 000");
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(game->height / 20);
    highScoreText.setPosition(sf::Vector2f(game->width - highScoreText.getGlobalBounds().width, game->height - highScoreText.getGlobalBounds().height * 2));

    scoreText.setPosition(sf::Vector2f(game->width - highScoreText.getGlobalBounds().width, game->height - highScoreText.getGlobalBounds().height * 3.5));

    highScoreText.setString("High Score: " + std::to_string(player.highScore));
}

void GameScreen::newGame()
{
    collision = backToMenu = false;
    pause = true;

    scoreText.setString("Score: " + std::to_string(player.score));

    flashCLK.restart();
}

void GameScreen::replay()
{
    newGame();
    player.newGame();
    ObstacleSpawner.newGame();
}

void GameScreen::handleInput()
{
    sf::Event event;

    while (game->window->pollEvent(event))
    {   
        if (!pause)
            player.handleInput(event);

        if (event.type == sf::Event::LostFocus)
            pause = true;

        else if (event.type == sf::Event::Closed)
            game->window->close();

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                if (MenuScreen::isSpritePressed(pauseButton, game->window))
                {
                    pause = !pause;
                    break;
                }
                if (player.isDead() || pause)
                {
                    if (MenuScreen::isSpritePressed(retryButton, game->window))
                    {
                        replay();
                        break;
                    }
                    else if (MenuScreen::isSpritePressed(menuButton, game->window))
                    {
                        backToMenu = true;
                        break;
                    }
                }
                pause = false;
                player.handleInput(event);
                break;
            }
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::R:
                if (pause || player.isDead())
                    replay();
                break;
            case sf::Keyboard::Space:
                pause = false;
                player.handleInput(event);
                break;
            case sf::Keyboard::Escape:
                pause = !pause;
                break;
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                // returns to menu if pressed Escape after player died
                if (player.isDead())
                    backToMenu = true;
                break;
            }
        }
    }
}

void GameScreen::update(float dt)
{
    // quad Tree is reconstructed every frame
    myTree.reset();

    if (backToMenu)
    {
        player.saveHighScore();
        game->previousScreen();
        return;
    }

    if (!pause || player.isCollided())
        pauseButton.setTexture(pauseIMG);
    else
        pauseButton.setTexture(playIMG);

    // moves player, object and background if no collisions && window is focused && game is not paused
    if (!player.isCollided())
        player.animate(dt);
    
    if (!pause)
    {
        ObstacleSpawner.update(dt);
        player.update(dt);
    }

    // collision detected
    if (!collision)
    {
        if (player.isCollided())
        {
            flashCLK.restart(); // quick flash display when player loses
            collision = true;
        }
    }

    // display text if new high score is detected
    if (player.isDead())
    {
        if (player.isNewHighScore())
        {
            scoreText.setString("Bravo!!");
            highScoreText.setString("High Score: " + std::to_string(player.highScore));
        }
    }
    else
        scoreText.setString("Score: " + std::to_string(player.score));
}

void GameScreen::draw()
{
    game->window->draw(sky);
    ObstacleSpawner.draw(game->window);

    game->window->draw(ground);
    game->window->draw(scoreText);
    game->window->draw(highScoreText);
    game->window->draw(pauseButton);
    player.draw(game->window);

    if (player.isDead() || pause)
    { // display buttons if game is paused or player loses
        game->window->draw(retryButton);
        game->window->draw(menuButton);
    }

    flashScreen(flashCLK, game);
}

void GameScreen::flashScreen(sf::Clock flashCLK, Game *game)
{
    // displays quick flash (white square) for a few milliseconds when dying or at restarting the game
    if (flashCLK.getElapsedTime().asSeconds() < FLASH_TIME)
    {
        sf::RectangleShape white(sf::Vector2f(game->width, game->height));

        white.setFillColor(sf::Color(255, 255, 255, 100));

        game->window->draw(white);
    }
}
