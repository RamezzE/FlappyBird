#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <functional>

#include "Player.hpp"
#include "QuadTree.hpp"
#include "Definitions.hpp"
#include "Common.hpp"
 
class Obstacle
{
public:
	Obstacle(Player* myPlayer,  QuadTree<sf::Sprite>* quadTree);

	void update(const float dt, Game *myGame);

	void draw(sf::RenderWindow* myWindow);

	void setGap(ushort verticalGap);

	void newGame();

private:

	Player* myPlayer;

	QuadTree<sf::Sprite>* myTree;
	
	sf::Texture upObstTexture, downObstTexture;
	
	sf::Sprite groundObstacle;

	std::deque<sf::Sprite> ObstacleSprites;

	ushort verticalGap;

	Game* game;

	float obstacleSpeed;

	void spawnObstacle();

	void spawnGroundObstacle();

	void moveObstacles(const float dt);

};

