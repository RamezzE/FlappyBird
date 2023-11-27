#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Button.hpp"

class SettingsOverlay
{
public:
	SettingsOverlay(Game* myGame);

	void handleInput(sf::Event event);
	void update(const float dt);
	void draw();

	bool isOn();

	void enable();
	void disable();
	
private:
	void init();
	Game* game;

	bool disabled;

	sf::RectangleShape background;
	sf::Texture bgIMG;

	Button buttons[3];

	sf::Texture buttonTextures[3];

	sf::Text buttonTexts[3];
	
	sf::Font font;
};
