#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
    startXpos = myWidth / 8; //starting x coordinate
    startYpos = myHeight / 2; //starting y cooridinate 

    upRotationLimit = 340;
    downRotationLimit = 10;
    rotation = 0;

    initializePlayer();
}

void Player::initializePlayer()
{
    //loading the 4 frame imgs of the bird
    playerSpriteSheet[0].loadFromFile(PLAYER_FRAME_1);
    playerSpriteSheet[1].loadFromFile(PLAYER_FRAME_2);
    playerSpriteSheet[2].loadFromFile(PLAYER_FRAME_3);
    playerSpriteSheet[3].loadFromFile(PLAYER_FRAME_4);

    //setting initial img for the player
    playerSprite.setTexture(playerSpriteSheet[0]);

    //setting scale and position
    float num = (float)myHeight / (float)playerSprite.getLocalBounds().height;
    num /= 15;
    playerSprite.setScale(num, num);
   
    playerSprite.setPosition(sf::Vector2f(startXpos, startYpos));

    sf::FloatRect temp;
    temp = playerSprite.getLocalBounds();
    playerSprite.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);

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

bool Player::jump(sf::Clock &clk,float dt) {

    // limits the up movement so bird doesnt get out of screen
    if (playerSprite.getPosition().y <= getHeight()) {
        velocity.y = 0;
        return false;
    }
    
    if (clk.getElapsedTime().asSeconds() > PLAYER_FLYING_DURATION) {
        return false;
    }

    velocity.y = 0;
    velocity.y -= PLAYER_SPEED;
    velocity.y += GRAVITY * dt;
    playerSprite.move(velocity * dt);

    return true;
}

bool Player::fall(float dt) {

    velocity.y += GRAVITY * dt;
    playerSprite.move(velocity * dt);
    if (velocity.y > 0) {
        rotation += ROTATION_SPEED * dt;

        if (rotation > 25.0f)
            rotation = 25.0f;

        playerSprite.setRotation(rotation);
    }
    else {
        cout << rotation << endl;
        rotation -= ROTATION_SPEED*3 * dt;

        if (rotation < -25.0f)
            rotation = -25.0f;

        playerSprite.setRotation(rotation);
    }

    return true;
}



bool Player::die(float dt, QuadTree::Rectangle playerRect, QuadTree& quadTree) {

    vector<sf::Sprite> spritesFound;
    quadTree.query(playerRect, spritesFound);

    // if collision with ground detected returns true as in fully died to display menu, retry buttons and other actions etc
    if (spritesFound.size() > 0) return true;

    //if no collision detected it continues the dying animation

    fall(dt);

    return false;
}

void Player::draw(sf::RenderWindow* myWindow)
{
    myWindow->draw(playerSprite);
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

float Player::getRotation()
{
    return playerSprite.getRotation();
}


