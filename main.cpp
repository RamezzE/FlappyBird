#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "src/hpp/Game.hpp"

unsigned short widthRatio, heightRatio, myWidth, myHeight;

int main()
{
    srand(time(NULL));

    const unsigned short screenWidth = sf::VideoMode::getDesktopMode().width;
    const unsigned short screenHeight = sf::VideoMode::getDesktopMode().height *0.9f;

    widthRatio = 3;
    heightRatio = 4;

    myWidth = 0, myHeight = 0;

    bool exitLoop = false;
    do
    {
        if (myWidth < screenWidth)
            myWidth += widthRatio;
        else
            exitLoop = true;

        if (!exitLoop)
        {
            if (myHeight < screenHeight)
                myHeight += heightRatio;
            else
                exitLoop = true;
        }

    } while (!exitLoop);

    Game myGame;
    myGame.changeScreen(ScreenType::MainMenu);
    myGame.gameLoop();
}
