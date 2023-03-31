#pragma once
#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include "Quadtree.h"
#include "Player.h"

 
class Obstacle
{
public:
	Obstacle(Player &myPlayer);

	sf::Sprite spawnGround();

	void update(float dt);

	void draw(sf::RenderWindow* myWindow);

	std::deque<sf::Sprite> getSprites();

	void setGap(unsigned short verticalGap);

	void newGame();


private:

	Player* myPlayer;

	sf::Texture upObstTexture;
	sf::Texture downObstTexture;

	sf::Sprite fakeObstacle;

	std::deque<sf::Sprite> ObstacleSprites;

	unsigned short verticalGap;

	void spawnObstacle();

	void spawnFakeGround();

	void moveObstacles(float dt);

};

