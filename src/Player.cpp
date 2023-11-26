#include "Player.hpp"
#include <iostream>

Player::Player(QuadTree<sf::Sprite> *quadTree)
{
    myTree = quadTree;
    init();
    newGame();
}

void Player::init()
{
    startXpos = myWidth / 8;  // starting x coordinate
    startYpos = myHeight / 2; // starting y cooridinate
    highScore = 0;

    // loading the 4 frame imgs of the bird
    playerSpriteSheet[0].loadFromFile(PLAYER_FRAME_1);
    playerSpriteSheet[1].loadFromFile(PLAYER_FRAME_2);
    playerSpriteSheet[2].loadFromFile(PLAYER_FRAME_3);
    playerSpriteSheet[3].loadFromFile(PLAYER_FRAME_4);


    playerSprite.setTexture(playerSpriteSheet[0]);

    // setting scale and position
    float scale = (float)myHeight / (float)playerSprite.getLocalBounds().height;
    scale /= 15;
    playerSprite.setScale(scale, scale);

    sf::FloatRect temp;
    temp = playerSprite.getLocalBounds();
    playerSprite.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);

    readHighScore();
}

void Player::newGame()
{
    rotation = score  = 0;
    velocity = sf::Vector2f(0, 0);
    collided = died = newHighScore = spacePressed = false;

    playerSprite.setPosition(sf::Vector2f(startXpos, startYpos));
    playerSprite.setRotation(rotation);
}

void Player::handleInput(sf::Event event)
{
    if (event.type == sf::Event::Closed)
        saveHighScore();
    
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            if (!spacePressed)
            {
                tap();
                spacePressed = true;
            }
        }
    }

    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Space)
            spacePressed = false;
    }
    
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
            tap();
    }
}

void Player::update(const float dt)
{
    if (collided)
    {
        if (die(dt))
        {
            died = true;
            saveHighScore();
        }
        return;
    }

    if (queryTree())
    {
        collided = true;
        velocity = sf::Vector2f(0, 0);
        return;
    }

    if (jumpCLK.getElapsedTime().asSeconds() <= PLAYER_FLYING_DURATION)
        jump(dt);
    else
        fall(dt);
}

void Player::draw(sf::RenderWindow *myWindow)
{
    myWindow->draw(playerSprite);
}

void Player::animate(const float dt)
{
    static float totalDT = 0;
    totalDT += dt;
    if (totalDT <= PLAYER_ANIMATION_DURATION)
        return; // limiting speed of changing frames

    totalDT = 0;
    static ushort x = 0;

    playerSprite.setTexture(playerSpriteSheet[x]);
    ++x %= 4;
}

void Player::jump(const float dt)
{
    // limits the up movement so bird doesnt get out of screen
    if (playerSprite.getPosition().y <= getHeight())
        return;

    velocity.y = 0;
    velocity.y -= PLAYER_SPEED;
    velocity.y += GRAVITY * dt;
    playerSprite.move(velocity * dt);
}

void Player::fall(const float dt)
{
    velocity.y += GRAVITY * dt;
    playerSprite.move(velocity * dt);
    if (velocity.y > 0)
    {
        rotation += ROTATION_SPEED * dt;

        if (rotation > 25.0f)
            rotation = 25.0f;

        playerSprite.setRotation(rotation);
        return;
    }
    
    rotation -= ROTATION_SPEED * 3 * dt;

    if (rotation < -25.0f)
        rotation = -25.0f;

    playerSprite.setRotation(rotation);
}

bool Player::die(const float dt)
{
    if (queryTree())
        return true;

    fall(dt);

    return false;
}

void Player::tap()
{
    jumpCLK.restart();
}

void Player::saveHighScore()
{
    if (score < highScore)
        return;

    newHighScore = true;
    highScore = score;

    // saves high Score into binary file
    std::ofstream fileWrite(HIGH_SCORE_FILEPATH, std::ios::out | std::ios::binary);
    fileWrite.write((char *)&highScore, sizeof(highScore));
    fileWrite.close();
}

void Player::readHighScore()
{
    // reads high score from binary file and saves it into highScore variable
    std::ifstream fileRead(HIGH_SCORE_FILEPATH, std::ios::in | std::ios::binary);
    fileRead.read((char *)&highScore, sizeof(highScore));
    fileRead.close();
}

bool Player::queryTree()
{
    std::vector<sf::Sprite *> spritesFound;
    myTree->query(playerSprite.getGlobalBounds(), spritesFound);

    for (ushort i = 0; i < spritesFound.size(); ++i)
    {
        if (Collision::PixelPerfectTest(playerSprite, *spritesFound[i]))
            return true;
    }
    return false;
}

float Player::getHeight()
{
    return playerSprite.getGlobalBounds().height;
}

bool Player::isCollided()
{
    return collided;
}

bool Player::isDead()
{
    return died;
}

bool Player::isNewHighScore()
{
    return newHighScore;
}