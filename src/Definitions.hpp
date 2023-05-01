#pragma once	
#include "Game.hpp"

#define PLAYER_FRAME_1 "assets\\pics\\bird\\frame-1.png"
#define PLAYER_FRAME_2 "assets\\pics\\bird\\frame-2.png"
#define PLAYER_FRAME_3 "assets\\pics\\bird\\frame-3.png"
#define PLAYER_FRAME_4 "assets\\pics\\bird\\frame-4.png"

#define SKY_FILEPATH "assets\\pics\\background\\SKY.png"
#define GROUND_FILEPATH "assets\\pics\\background\\ground.png"

#define OBSTACLE_UP_FILEPATH "assets\\pics\\obstacles\\wood_log_up.png"
#define OBSTACLE_DOWN_FILEPATH "assets\\pics\\obstacles\\wood_log_down.png"

#define MENU_BACKGROUND "assets\\pics\\background\\gamebg2.jpg"
#define PLAY_BUTTON "assets\\pics\\menu\\play.png"
#define CLOSE_BUTTON "assets\\pics\\menu\\close.png"
#define RETRY_BUTTON "assets\\pics\\menu\\restart.png"
#define MENU_BUTTON "assets\\pics\\menu\\menu.png"
#define PAUSE_BUTTON "assets\\pics\\menu\\pause.png"
#define SETTINGS_BUTTON "assets\\pics\\menu\\setting.png"

#define FONT_FILEPATH "assets\\fonts\\soup_of_justice\\soupofjustice.ttf"

#define HIGH_SCORE_FILEPATH "assets\\files\\highScore.dat"

#define PLAYER_ANIMATION_DURATION 0.08f

#define PLAYER_FLYING_DURATION 0.01f
#define PLAYER_SPEED myHeight/1.5f
#define GRAVITY PLAYER_SPEED * 3.5f
#define OBSTACLE_SPEED PLAYER_SPEED/2.0f
#define DISTANCE_BETWEEN_OBSTACLES myWidth/3.0f

#define ROTATION_SPEED 150.0f

#define FLASH_TIME 0.1f

typedef unsigned short ushort;
extern ushort myWidth, myHeight;