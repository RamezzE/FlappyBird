#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "GameScreen.h"
class MenuScreen
{
public:
	MenuScreen(sf::RenderWindow& myWindow);

	void gameLoop();
	void handleInput();
	void update();
	void draw();

	void initialize();
	static bool isSpritePressed(sf::Sprite sprite, sf::RenderWindow* myWindow);

private:


	sf::RenderWindow* myWindow;

	sf::RectangleShape background;
	sf::Texture backIMG;

	sf::Sprite playButton;
	sf::Sprite closeButton;

	sf::Texture playButtonTexture;
	sf::Texture closeButtonTexture;

	sf::Text title;
	sf::Font font;

	bool startGame;

};

