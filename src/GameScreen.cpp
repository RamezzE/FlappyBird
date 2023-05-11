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

    skyIMG.loadFromFile(SKY_FILEPATH);
    groundIMG.loadFromFile(GROUND_FILEPATH);
    buttonTextures[0].loadFromFile(MENU_BUTTON);
    buttonTextures[1].loadFromFile(RETRY_BUTTON);
    buttonTextures[2].loadFromFile(PAUSE_BUTTON);
    buttonTextures[3].loadFromFile(PLAY_BUTTON);


    sky.setTexture(&skyIMG);
    ground.setTexture(&groundIMG);

    // setting background size
    sky.setSize(sf::Vector2f(game->width * 1.5, game->height));
    ground.setSize(sf::Vector2f(game->width * 1.5, game->height));

    // setting buttons textures, size, scale, position etc
    for (ushort i = 0; i < 3; i++)
        buttons[i].setTexture(buttonTextures[i]);

    float scale = (float)game->height / (float)buttons[0].getLocalBounds().height;
    scale /= 10;

    for (ushort i = 0, j = 3; i < 3; i++, j--)
    {
        buttons[i].setScale(sf::Vector2f(scale, scale));
        buttons[i].setPosition(sf::Vector2f(game->width - (buttons[i].getGlobalBounds().width * (j) + game->width * 0.005f * (j)), game->height * 0.005f));
    }

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

        else if (event.type == sf::Event::MouseButtonReleased)
        {
            for (ushort i = 0; i < 3; i++)
                buttons[i].setColor(sf::Color::White);

            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                if (Input::isMouseOver(buttons[2], game->window))
                {
                    pause = !pause;
                    break;
                }
                if (player.isDead() || pause)
                {
                    if (Input::isMouseOver(buttons[0], game->window))
                    {
                        backToMenu = true;
                        break;
                    }
                    else if (Input::isMouseOver(buttons[1], game->window))
                    {
                        replay();
                        break;
                    }
                }
            }
        }

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            bool exit = false;
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                for (ushort i = 0; i < 3; i++)
                    if (Input::isMouseOver(buttons[i], game->window))
                    {
                        buttons[i].setColor(sf::Color(178, 178, 178, 255));
                        exit = true;
                    }
                    else
                        buttons[i].setColor(sf::Color::White);
                break;
            }

            if (exit)
                break;

            pause = false;
            player.handleInput(event);
            break;
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
        buttons[2].setTexture(buttonTextures[2]);
    else
        buttons[2].setTexture(buttonTextures[3]);

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
    game->window->draw(buttons[2]);
    player.draw(game->window);

    if (player.isDead() || pause)
    { // display buttons if game is paused or player loses
        for (ushort i = 0; i < 2; i++)
            game->window->draw(buttons[i]);
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
