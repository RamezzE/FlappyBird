#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

#include "Definitions.hpp"
#include "Quadtree.hpp"
#include "Player.hpp"
#include "Collision.hpp"
 
class Obstacle
{
public:
	Obstacle(Player* myPlayer,  QuadTree<sf::Sprite>* quadTree);

	void update(const float dt);

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

	void spawnObstacle();

	void spawnGroundObstacle();

	void moveObstacles(const float dt);

};

