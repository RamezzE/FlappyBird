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
	Obstacle(Player &myPlayer);

	sf::Sprite spawnGround();

	void update(float dt);

	void draw(sf::RenderWindow* myWindow);

	deque<sf::Sprite> getSprites();

	void setGap(unsigned short distanceBetweenObstacles, unsigned short verticalGap);

	void newGame();


private:

	Player* myPlayer;

	sf::Texture upObstTexture;
	sf::Texture downObstTexture;

	sf::Sprite fakeObstacle;

	deque<sf::Sprite> ObstacleSprites;

	unsigned short verticalGap, distanceBetweenObstacles;

	float movementSpeed;

	void spawnObstacle();

	void spawnFakeGround();

	void moveObstacles(float dt);

};

