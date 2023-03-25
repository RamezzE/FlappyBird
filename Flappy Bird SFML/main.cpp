// Helicopter Game DST Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Quadtree.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "MenuScreen.h"

using namespace std;

//still need to create a button class and adjust all sprite scales

unsigned short widthRatio, heightRatio, myWidth, myHeight;

int main()
{
    // hiding console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, 1);

    srand(time(NULL));

    unsigned short screenWidth = sf::VideoMode::getDesktopMode().width;
    unsigned short screenHeight = sf::VideoMode::getDesktopMode().height*0.9;
    
    widthRatio = 3;  heightRatio = 4;

    myWidth = 0, myHeight = 0;
    
    bool exitLoop = false;
    do {
        if (myWidth < screenWidth) {
            myWidth += widthRatio;
        }
        else {
            exitLoop = true;
        }
        if (!exitLoop) {
            if (myHeight < screenHeight) {
                myHeight += heightRatio;
            }
            else {
                exitLoop = true;
            }
        }


    } while (!exitLoop);

    //myWidth = 300; myHeight = 400;
    /*myWidth = sf::VideoMode::getDesktopMode().width/2;
    myHeight = sf::VideoMode::getDesktopMode().height;*/


    sf::RenderWindow myWindow;

    //myWindow.create(sf::VideoMode(myWidth,myHeight), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);
    myWindow.create(sf::VideoMode(myWidth, myHeight), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);

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
