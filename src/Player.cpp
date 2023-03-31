#include "Player.h"
#include <iostream>
 

Player::Player()
{
    init();
    newGame();
}

void Player::init()
{
    startXpos = myWidth / 8; //starting x coordinate
    startYpos = myHeight / 2; //starting y cooridinate 
    highScore = 0;

    //loading the 4 frame imgs of the bird
    playerSpriteSheet[0].loadFromFile(PLAYER_FRAME_1);
    playerSpriteSheet[1].loadFromFile(PLAYER_FRAME_2);
    playerSpriteSheet[2].loadFromFile(PLAYER_FRAME_3);
    playerSpriteSheet[3].loadFromFile(PLAYER_FRAME_4);
    playerSprite.setTexture(playerSpriteSheet[0]);
    //setting scale and position
    float num = (float)myHeight / (float)playerSprite.getLocalBounds().height;
    num /= 15;
    playerSprite.setScale(num, num);
    
    sf::FloatRect temp;
    temp = playerSprite.getLocalBounds();
    playerSprite.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
}

void Player::newGame() {
    rotation = score = 0;

    playerSprite.setPosition(sf::Vector2f(startXpos, startYpos));
    playerSprite.setRotation(rotation);
    //setting initial img for the player
    
    readHighScore();
}

void Player::update(float dt)
{
    if (jumpCLK.getElapsedTime().asSeconds() <= PLAYER_FLYING_DURATION)
        jump(dt);
    else
        fall(dt);
}

void Player::draw(sf::RenderWindow* myWindow)
{
    myWindow->draw(playerSprite);
}

void Player::animate(float dt) {

    static float totalDT = 0;
    totalDT += dt;
    if (totalDT <= PLAYER_ANIMATION_DURATION) return; //limiting speed of changing frames
    else totalDT = 0;

    static unsigned short x = 0;

    playerSprite.setTexture(playerSpriteSheet[x]);
    ++x %= 4;

}

void Player::jump(float dt) {

    // limits the up movement so bird doesnt get out of screen
    if (playerSprite.getPosition().y <= getHeight()) {
        velocity.y = 0;
        return;
    }

    velocity.y = 0;
    velocity.y -= PLAYER_SPEED;
    velocity.y += GRAVITY * dt;
    playerSprite.move(velocity * dt);
}

void Player::fall(float dt) {

    velocity.y += GRAVITY * dt;
    playerSprite.move(velocity * dt);
    if (velocity.y > 0) {
        rotation += ROTATION_SPEED * dt;

        if (rotation > 25.0f)
            rotation = 25.0f;

        playerSprite.setRotation(rotation);
    }
    else {
        rotation -= ROTATION_SPEED*3 * dt;

        if (rotation < -25.0f)
            rotation = -25.0f;

        playerSprite.setRotation(rotation);
    }
}

bool Player::die(float dt, QuadTree::Rectangle playerRect, QuadTree& quadTree) {

     std::vector<sf::Sprite> spritesFound;
    quadTree.query(playerRect, spritesFound);

    // if collision with ground detected returns true as in fully died to display menu, retry buttons and other actions etc
    if (spritesFound.size() > 0)
        return true;
    //if no collision detected it continues the dying animation

    fall(dt);

    return false;
}

void Player::tap()
{
    jumpCLK.restart();
}

void Player::saveHighScore()
{
    if (score < highScore) return;

    highScore = score;

    //saves high Score into binary file
    std::ofstream fileWrite(HIGH_SCORE_FILEPATH, std::ios::out | std::ios::binary);
    fileWrite.write((char*)&highScore, sizeof(highScore));
    fileWrite.close();

}

void Player::readHighScore()
{
    //reads high score from binary file and saves it into highScore variable
    std::ifstream fileRead(HIGH_SCORE_FILEPATH, std::ios::in | std::ios::binary);
    fileRead.read((char*)&highScore, sizeof(highScore));
    fileRead.close();

}

//some setters & getters
void Player::setVelocity(float x, float y)
{
    this->velocity = sf::Vector2f(x, y);
}

void Player::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

float Player::getX()
{
    return playerSprite.getPosition().x;
}

float Player::getY()
{
    return playerSprite.getPosition().y;
}

float Player::getHeight()
{
    return playerSprite.getGlobalBounds().height;
}

float Player::getWidth()
{
    return playerSprite.getGlobalBounds().width;
}


