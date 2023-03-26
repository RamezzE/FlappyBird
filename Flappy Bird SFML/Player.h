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

	bool jump(sf::Clock &clk, float dt);
	bool fall(float dt);

	void setVelocity(float x, float y);
	void setVelocity(sf::Vector2f velocity);

	void draw(sf::RenderWindow* myWindow);

	bool die(float dt, QuadTree::Rectangle playerRect, QuadTree& quadTree);

	float getX();
	float getY();
	float getHeight();
	float getWidth();
	float getRotation();

private:
	sf::Texture playerSpriteSheet[4];
	sf::Sprite playerSprite;
	
	sf::Vector2f velocity;
	unsigned short  upRotationLimit, downRotationLimit;
	float rotation;
	void initializePlayer();
	
};

