#pragma once
#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include "Quadtree.h"
#include "Player.h"

using namespace std;
class Obstacle
{
public:
	Obstacle();

	void spawnObstacle();

	sf::Sprite spawnGround();

	void drawObstacles(sf::RenderWindow* myWindow);

	bool moveObstacles(QuadTree& quadTree, float dt, Player player, unsigned short& score);

	void setGap(unsigned short distanceBetweenObstacles, unsigned short verticalGap);

	deque<sf::Sprite> ObstacleSprites;

private:

	sf::Texture upObstTexture;
	sf::Texture downObstTexture;

	sf::Sprite fakeObstacle;

	unsigned short verticalGap, distanceBetweenObstacles;

	float movementSpeed;

	void spawnFakeGround();
};

