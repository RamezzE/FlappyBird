#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Screens.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"



typedef unsigned short ushort;

class Game
{
public:
	Game();
	~Game();

	void changeScreen(ScreenType screen);
	void gameLoop();

	void pause();
	void resume();
	void togglePause();

	bool isPaused();

	sf::RenderWindow *window;

	ushort width, height;
	
private:
	std::vector<GameState *> states;
	std::vector<ScreenType> StoredScreens;

	GameState *CurrentState();

	void pushState(GameState *state, ScreenType screen);
	void cycleStates();
	void popState();

	bool pauseGame;
	sf::Image icon;
};