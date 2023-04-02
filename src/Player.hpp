#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Definitions.hpp"
#include "Quadtree.hpp"



class Player
{
public:
	unsigned short startXpos, startYpos, score, highScore;

	Player();
	void newGame();

	void animate(float dt);
	
	void setVelocity(float x, float y);
	void setVelocity(sf::Vector2f velocity);

	void update(float dt);

	void draw(sf::RenderWindow* myWindow);

	void tap();

	bool die(float dt, QuadTree& quadTree);

	float getX();
	float getY();
	float getHeight();
	float getWidth();
	sf::Sprite getSprite();
	
	void saveHighScore();
	
private:
	sf::Texture playerSpriteSheet[4];
	sf::Sprite playerSprite;
	
	sf::Vector2f velocity;

	sf::Clock jumpCLK;

	float rotation;
	void init();

	void jump(float dt);
	void fall(float dt);

	void readHighScore();
	
};

