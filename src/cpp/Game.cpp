
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../hpp/Game.hpp"
#include "../hpp/MenuScreen.hpp"
#include "../hpp/GameScreen.hpp"

Game::Game()
{
	window = new sf::RenderWindow();
	width = myWidth;
	height = myHeight;

	window->create(sf::VideoMode(width, height), "FlarKy Bird", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
	window->setPosition(sf::Vector2i(window->getPosition().x, 10));

	icon.loadFromFile(PLAYER_FRAME_1);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	pauseGame = true;
	difficulty = Difficulty::Normal;
	
	// loading music
	music.openFromFile(MUSIC_FILEPATH);
	music.setLoop(true);
	music.play();
}

void Game::changeScreen(ScreenType newScreen)
{
	pauseGame = true;
	// Switch to the requested screen type
	switch (newScreen)
	{
	case ScreenType::MainMenu:
		// If the screen is not already stored, store it
		if (std::find(StoredScreens.begin(), StoredScreens.end(), newScreen) == StoredScreens.end())
			pushState(new MenuScreen(this), newScreen);
		else // If the screen is already stored, cycle through the stored screens until the requested screen is reached
			while (StoredScreens.back() != newScreen)
				cycleStates();
		break;

	case ScreenType::Gameplay:
		// If the screen is not already stored, store it
		if (std::find(StoredScreens.begin(), StoredScreens.end(), newScreen) == StoredScreens.end())
			pushState(new GameScreen(this), newScreen);
		else // If the screen is already stored, cycle through the stored screens until the requested screen is reached
			while (StoredScreens.back() != newScreen)
				cycleStates();
		break;
	}
}

void Game::cycleStates()
{
	if (StoredScreens.size() == 1)
		return;

	// keeping record of the states
	StoredScreens.push_back(StoredScreens.front());
	StoredScreens.erase(StoredScreens.begin());

	// Move the front state to the back
	states.push_back(states.front());
	states.erase(states.begin());
}

void Game::pushState(GameState *state, ScreenType screen)
{
	states.push_back(state);
	StoredScreens.push_back(screen);
}

void Game::popState()
{
	if (states.empty())
		return;

	delete states.back();
	states.pop_back();
}

Game::~Game()
{
	while (!states.empty())
		popState();


	music.stop();

	delete window;
}

GameState *Game::CurrentState()
{
	if (states.empty())
		return nullptr;
	else
		return states.back();
}

void Game::gameLoop()
{
	sf::Clock clk;
	float dt;

	while (window->isOpen())
	{

		dt = clk.restart().asSeconds();

		if (CurrentState() == nullptr)
			continue;

		CurrentState()->handleInput();

		CurrentState()->update(dt);

		window->clear();

		CurrentState()->draw();

		window->display();
	}
}

void Game::pause()
{
	pauseGame = true;
}

void Game::resume()
{
	pauseGame = false;
}

void Game::togglePause()
{
	pauseGame = !pauseGame;
}

bool Game::isPaused()
{
	return pauseGame;
}

void Game::setDifficulty(Difficulty difficulty)
{
	this->difficulty = difficulty;
}

Difficulty Game::getDifficulty()
{
	return difficulty;
}
