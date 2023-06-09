//
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "Game.hpp"
#include "MenuScreen.hpp"
#include "GameScreen.hpp"

// still need to create a button class

unsigned short widthRatio, heightRatio, myWidth, myHeight;

int main()
{
    // hiding console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, 0);

    srand(time(NULL));

    unsigned short screenWidth = sf::VideoMode::getDesktopMode().width;
    unsigned short screenHeight = sf::VideoMode::getDesktopMode().height * 0.9;

    widthRatio = 3;
    heightRatio = 4;

    myWidth = 0, myHeight = 0;

    bool exitLoop = false;
    do
    {
        if (myWidth < screenWidth)
        {
            myWidth += widthRatio;
        }
        else
        {
            exitLoop = true;
        }
        if (!exitLoop)
        {
            if (myHeight < screenHeight)
            {
                myHeight += heightRatio;
            }
            else
            {
                exitLoop = true;
            }
        }

    } while (!exitLoop);

    // myWidth = 390; myHeight = 520;
    // myWidth = sf::VideoMode::getDesktopMode().width;
    // myHeight = sf::VideoMode::getDesktopMode().height;

    Game myGame;
    myGame.changeScreen(new MenuScreen(&myGame));
    myGame.gameLoop();
}