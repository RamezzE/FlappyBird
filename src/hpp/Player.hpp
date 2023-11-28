#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

#include "Game.hpp"
#include "QuadTree.hpp"
#include "Common.hpp"

class Player
{
public:
	ushort startXpos, startYpos, score, highScore;

	Player(QuadTree<sf::Sprite>* quadTree);
	
	void newGame();

	void animate(const float dt);

	void handleInput(sf::Event event, Game *myGame);

	void update(const float dt, Game *myGame);

	void draw(sf::RenderWindow* myWindow);

	void tap();

	bool queryTree();

	float getHeight();

	bool isCollided();
	bool isDead();
	bool isNewHighScore();

	void saveHighScore();
	
private:
	sf::Texture playerSpriteSheet[4];
	sf::Sprite playerSprite;
	
	sf::Vector2f velocity;

	sf::Clock jumpCLK;

	QuadTree<sf::Sprite>* myTree;
	
	bool collided, died, newHighScore, spacePressed;

	float rotation;
	void init();

	void jump(const float dt);
	void fall(const float dt);

	bool die(const float dt);
	void readHighScore();

	sf::SoundBuffer dieBuffer, collideBuffer;
	sf::Sound dieSound, collideSound;
};

