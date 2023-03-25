#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "Quadtree.h"


class Player
{
public:
	unsigned short startXpos, startYpos;

	Player();
	void animate(float dt);

	bool moveUp(float dt, float rotationAngle = 100);
	bool moveDown(float dt, float rotationAngle = 100);

	void draw(sf::RenderWindow* myWindow);

	bool die(float dt, QuadTree::Rectangle playerRect, QuadTree& quadTree);

	unsigned short getX();
	unsigned short getY();
	unsigned short getHeight();
	unsigned short getWidth();
	unsigned short getRotation();

private:
	sf::Texture playerSpriteSheet[4];
	sf::Sprite playerSprite;
	sf::Clock moveUpCLK;

	float movementSpeed;

	unsigned short  upRotationLimit, downRotationLimit;
	void initializePlayer();

};

