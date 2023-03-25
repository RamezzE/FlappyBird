#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
    startXpos = SCREEN_WIDTH / 8; //starting x coordinate
    startYpos = SCREEN_HEIGHT / 2; //starting y cooridinate 

    movementSpeed = 200;

    upRotationLimit = 340;
    downRotationLimit = 10;

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
    playerSprite.setScale(0.1, 0.1);
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

bool Player::moveUp(float dt, float rotationAngle) {

    // limits the up movement so bird doesnt get out of screen
    if (playerSprite.getPosition().y <= getHeight() / 2) return false;

    playerSprite.move(0, -movementSpeed * dt);

    // adjusting rotation
    if (getRotation() < downRotationLimit + 5 || getRotation() > upRotationLimit) {
        playerSprite.rotate(-rotationAngle * dt);
    }

    return true;
}

bool Player::moveDown(float dt, float rotationAngle) {

    playerSprite.move(0, movementSpeed * dt);

    //adjusting rotation
    if (getRotation() > upRotationLimit - 5 || getRotation() < downRotationLimit) {
        playerSprite.rotate(rotationAngle * dt);
    }

    return true;
}

bool Player::die(float dt, QuadTree::Rectangle playerRect, QuadTree& quadTree) {

    vector<sf::Sprite> spritesFound;
    quadTree.query(playerRect, spritesFound);

    // if collision with ground detected returns true as in fully died to display menu, retry buttons and other actions etc
    if (spritesFound.size() > 0) return true;

    //if no collision detected it continues the dying animation
    playerSprite.move(movementSpeed / 2 * dt, movementSpeed * 1.2 * dt);

    playerSprite.rotate(100 * dt);

    return false;
}

void Player::draw(sf::RenderWindow* myWindow)
{
    myWindow->draw(playerSprite);
}


//some getters
unsigned short Player::getX()
{
    return playerSprite.getPosition().x;
}

unsigned short Player::getY()
{
    return playerSprite.getPosition().y;
}

unsigned short Player::getHeight()
{
    return playerSprite.getGlobalBounds().height;
}

unsigned short Player::getWidth()
{
    return playerSprite.getGlobalBounds().width;
}

unsigned short Player::getRotation()
{
    return playerSprite.getRotation();
}
