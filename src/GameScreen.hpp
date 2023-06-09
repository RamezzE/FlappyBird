#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Definitions.hpp"
#include "MenuScreen.hpp"
#include "Player.hpp"
#include "Quadtree.hpp"
#include "Obstacle.hpp"
#include "Common.hpp"
#include "Button.hpp"

#include "Game.hpp"
#include "GameState.hpp"

class GameScreen : public GameState
{
public:
	GameScreen(Game *game);

	void handleInput();
	void update(float dt);
	void draw();

private:
	void init();

	void replay();

	Game *game;

	static void flashScreen(sf::Clock flashCLK, Game *game);

	QuadTree<sf::Sprite> myTree;
	sf::FloatRect boundary;
	sf::RectangleShape sky, ground;

	sf::Clock flashCLK;

	sf::Texture skyIMG, groundIMG;
	
	Button buttons[3]; // 0 = menu, 1 = retry, 2 = pause

	sf::Texture buttonTextures[4]; // 0 = menu, 1 = retry, 2 = pause, 3 = play

	sf::Text scoreText, highScoreText;
	sf::Font font;

	Player player;

	Obstacle ObstacleSpawner;

	bool collision, pause, backToMenu;

	void newGame();
};
