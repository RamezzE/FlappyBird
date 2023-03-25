// Helicopter Game DST Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Quadtree.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "Definitions.h"
#include "MenuScreen.h"


#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

using namespace std;

int main()
{
    // hiding console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, 0);

    srand(time(NULL));

    sf::RenderWindow myWindow;

    myWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);

    //setting framerate limit 
    myWindow.setFramerateLimit(60);

    //starting with the menu screen
    MenuScreen menu(myWindow);
    menu.initialize();
    menu.gameLoop();

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
