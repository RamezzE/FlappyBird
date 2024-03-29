#include "../hpp/GameScreen.hpp"
#include <iostream>

GameScreen::GameScreen(Game *myGame)
    : ObstacleSpawner(Obstacle(&player, &myTree)),
      player(Player(&myTree))
{
    this->game = myGame;

    // setting QuadTree boundary to the whole screen
    boundary = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(game->width, game->height));
    myTree = QuadTree<sf::Sprite>(boundary, 1);

    skyIMG.loadFromFile(SKY_FILEPATH);
    groundIMG.loadFromFile(GROUND_FILEPATH);
    ground2IMG.loadFromFile(GROUND_FILEPATH);

    buttonTextures[0].loadFromFile(MENU_BUTTON);
    buttonTextures[1].loadFromFile(RETRY_BUTTON);
    buttonTextures[2].loadFromFile(PAUSE_BUTTON);
    buttonTextures[3].loadFromFile(PLAY_BUTTON);

    sky.setTexture(&skyIMG);
    ground.setTexture(&groundIMG);
    ground2.setTexture(&ground2IMG);
    
    for (ushort i = 0; i < 3; i++)
        buttons[i].setTexture(buttonTextures[i]);

    init();
    newGame();
}
void GameScreen::init()
{
    // setting background size
    sky.setSize(sf::Vector2f(game->width * 1.5, game->height));
    ground.setSize(sf::Vector2f(game->width * 1.5, game->height));
    ground2.setSize(sf::Vector2f(game->width * 1.5, game->height));

    ground.setPosition(sf::Vector2f(game->width - ground.getSize().y,0));
    ground2.setPosition(sf::Vector2f(ground.getPosition().x + ground.getSize().x, 0));

    ObstacleSpawner.setGap(player.getHeight() * 2.7f);

    // std::cout << (float)(player.getHeight() * 2.7f)/game->height << std::endl;
    // setting buttons textures, size, scale, position etc
    
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

    difficulty.setString("Normal Difficulty");
    difficulty.setFont(font);
    difficulty.setCharacterSize(game->height / 30);

    difficulty.setPosition(sf::Vector2f(game->width*0.05f, game->height * 0.005f));
    difficulty.setFillColor(sf::Color::Red);

    // setting up buttons onAction functions
    buttons[0].setOnAction([this]()
    { 
        player.saveHighScore();
        game->changeScreen(ScreenType::MainMenu);
        replay();
    });

    buttons[1].setOnAction([this]()
    {
        replay(); 
    });

    buttons[2].setOnAction([this]()
    {
        game->togglePause();
    });
}

void GameScreen::newGame()
{
    collision = false;
    game->pause();

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
        if (event.type == sf::Event::LostFocus)
            game->pause();

        else if (event.type == sf::Event::Closed)
            game->window->close();

        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::R:
                if (game->isPaused() || player.isDead())
                    replay();
                break;
            case sf::Keyboard::Escape:
                game->pause();
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
                    buttons[0].getOnAction()();
                break;
            }
        }

        for (ushort i = 0; i < 3; i++)
            buttons[i].handleInput(event);

        bool mouseOver = false;
        for (ushort i = 0; i < 3; i++)
            if (buttons[i].isMouseOver()) {
                mouseOver = true;
                break;
            }
        
        if (!mouseOver)
            player.handleInput(event, game);
    }
}

void GameScreen::update(float dt)
{

    if (!game->isPaused() && !player.isDead() && !player.isCollided())
        loopGround(dt);
    
    // quad Tree is reconstructed every frame
    myTree.reset();

    // You have to update ObstacleSpawner before player
    ObstacleSpawner.update(dt, game);
    player.update(dt, game);

    for (ushort i = 0; i < 3; i++)
        buttons[i].update(game->window);

    if (!game->isPaused() || player.isCollided())
        buttons[2].setTexture(buttonTextures[2]);
    else
        buttons[2].setTexture(buttonTextures[3]);

    // collision detected
    if (!collision)
    {
        if (player.isCollided())
        {
            flashCLK.restart(); // quick flash display when player loses
            collision = true;
        }
    }

    if (player.isDead() || game->isPaused())
        for (ushort i = 0; i < 2; i++)
            buttons[i].setDisabled(false);
    else 
        for (ushort i = 0; i < 2; i++)
            buttons[i].setDisabled(true);

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

    // if window size is changed, resize everything
    if (sky.getSize().y != game->height)
        init();

    switch (game->getDifficulty())
    {
    case Difficulty::Normal:
        difficulty.setString("Normal Difficulty");
        break;
    case Difficulty::Hard:
        difficulty.setString("Hard Difficulty");
        break;
    case Difficulty::Extreme:
        difficulty.setString("Extreme Difficulty");
        break;
    }
}

void GameScreen::draw()
{
    game->window->draw(sky);
    ObstacleSpawner.draw(game->window);

    game->window->draw(ground);
    game->window->draw(ground2);
    game->window->draw(scoreText);
    game->window->draw(highScoreText);

    if (game->isPaused() || player.isDead())
        game->window->draw(difficulty);

    for (ushort i = 0; i < 3; i++)  
        buttons[i].render(game->window);
    
    player.draw(game->window);
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

void GameScreen::loopGround(const float dt)
{
    // loops background
    ground.move(-BACKGROUND_LOOP_SPEED * dt, 0);
    ground2.move(-BACKGROUND_LOOP_SPEED * dt, 0);

    if (ground.getPosition().x + ground.getGlobalBounds().width < 0)
        ground.setPosition(sf::Vector2f(ground2.getPosition().x + ground2.getGlobalBounds().width, 0));

    if (ground2.getPosition().x + ground2.getGlobalBounds().width < 0)
        ground2.setPosition(sf::Vector2f(ground.getPosition().x + ground.getGlobalBounds().width, 0));
}
