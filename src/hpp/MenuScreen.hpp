#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Button.hpp"
#include "SettingsOverlay.hpp"

class MenuScreen : public GameState
{
public:
	MenuScreen(Game* myGame);

	void handleInput();
	void update(const float dt);
	void draw();
	
private:
	void init();
	Game* game;
	SettingsOverlay settings;

	sf::RectangleShape background;
	sf::Texture bgIMG;

	Button buttons[3]; // [0] = playButton, [1] = closeButton, [2] = settingsButton

	sf::Texture buttonTextures[3];

	sf::Text title;
	sf::Font font;

};
