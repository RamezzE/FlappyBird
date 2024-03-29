#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Screens.hpp"
#include "Difficulty.hpp"
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

	void setMusicVolume(float volume);
	// void setSoundVolume(float volume);
	float getMusicVolume();

	void setDifficulty(Difficulty difficulty);
	Difficulty getDifficulty();

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

	sf::Music music;

	Difficulty difficulty;
};