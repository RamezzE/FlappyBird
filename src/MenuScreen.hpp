#pragma once

#include <SFML/Graphics.hpp>

#include "Definitions.hpp"
#include "GameState.hpp"
#include "Game.hpp"
#include "GameScreen.hpp"
#include "Collision.hpp"

class MenuScreen : public GameState
{
public:
	MenuScreen(Game* myGame);

	void handleInput();
	void update(const float dt);
	void draw();
	
	static bool isSpritePressed(sf::Sprite sprite, sf::RenderWindow* myWindow);

private:
	void init();
	Game* game;

	bool startGame;

	sf::RectangleShape background;
	sf::Texture bgIMG;

	sf::Sprite playButton, closeButton;

	sf::Texture playButtonTexture, closeButtonTexture;

	sf::Text title;
	sf::Font font;

};

