#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "MenuScreen.h"
#include "Player.h"
#include "Quadtree.h"
#include "Obstacle.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class GameScreen
{
public:
	GameScreen(sf::RenderWindow& window);

	void initialize();

	void gameLoop();

	void replay();

	void draw();

	void update();

	void handleInput();



private:
	sf::RenderWindow* myWindow;

	QuadTree myTree;
	QuadTree::Rectangle boundary;

	Obstacle myObstacle;

	sf::RectangleShape sky;
	sf::RectangleShape ground;

	sf::Clock flashCLK;

	sf::Texture skyIMG;
	sf::Texture groundIMG;

	sf::Sprite retryButton;
	sf::Sprite menuButton;
	sf::Sprite pauseButton;

	sf::Texture retryIMG;
	sf::Texture menuIMG;
	sf::Texture pauseIMG;
	sf::Texture playIMG;

	sf::Text scoreText;
	sf::Text highScoreText;
	sf::Font font;

	Player myPlayer;
	QuadTree::Rectangle playerRect;
	vector<sf::Sprite> obstaclesFound;

	sf::Sprite currentObstacle;

	bool moveUp, collision, focus, pause, died, backToMenu, newHighScore;

	unsigned short score, highScore;

	float dt;

	void initializeTree();

	void flashScreen();

	void saveHighScore();

	void readHighScore();
};

