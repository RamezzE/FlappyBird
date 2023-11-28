#pragma once	

#define PLAYER_FRAME_1 "assets\\pics\\bird\\frame-1.png"
#define PLAYER_FRAME_2 "assets\\pics\\bird\\frame-2.png"
#define PLAYER_FRAME_3 "assets\\pics\\bird\\frame-3.png"
#define PLAYER_FRAME_4 "assets\\pics\\bird\\frame-4.png"

#define SKY_FILEPATH "assets\\pics\\background\\SKY.png"
#define GROUND_FILEPATH "assets\\pics\\background\\ground.png"

#define OBSTACLE_UP_FILEPATH "assets\\pics\\obstacles\\wood_log_up.png"
#define OBSTACLE_DOWN_FILEPATH "assets\\pics\\obstacles\\wood_log_down.png"

#define MENU_BACKGROUND "assets\\pics\\background\\gamebg2.jpg"
#define SETTINGS_BACKGROUND "assets\\pics\\settings\\bg.png"
#define SETTINGS_TABLE "assets\\pics\\settings\\table.png"

#define PLAY_BUTTON "assets\\pics\\menu\\play.png"
#define CLOSE_BUTTON "assets\\pics\\menu\\close.png"
#define RETRY_BUTTON "assets\\pics\\menu\\restart.png"
#define MENU_BUTTON "assets\\pics\\menu\\menu.png"
#define PAUSE_BUTTON "assets\\pics\\menu\\pause.png"
#define SETTINGS_BUTTON "assets\\pics\\menu\\setting.png"

#define SETTINGS_CLOSE_BUTTON "assets\\pics\\settings\\close_2.png"
#define SOUND_ON_BUTTON "assets\\pics\\settings\\sound_on.png"
#define SOUND_OFF_BUTTON "assets\\pics\\settings\\sound_off.png"
#define MUSIC_ON_BUTTON "assets\\pics\\settings\\music_on.png"
#define MUSIC_OFF_BUTTON "assets\\pics\\settings\\music_off.png"

#define NEXT_BUTTON "assets\\pics\\settings\\next.png"

#define BIRD_JUMP_SOUND "assets\\sounds\\bird_jump2.wav"
#define BIRD_COLLIDE_SOUND "assets\\sounds\\bird_collide.wav"
#define BIRD_DIE_SOUND "assets\\sounds\\bird_die.wav"

#define MUSIC_FILEPATH "assets\\music\\music.wav"

#define FONT_FILEPATH "assets\\fonts\\soup_of_justice\\soupofjustice.ttf"

#define HIGH_SCORE_FILEPATH "assets\\files\\highScore.dat"

#define PLAYER_ANIMATION_DURATION 0.08f

#define PLAYER_FLYING_DURATION 0.01f
#define PLAYER_SPEED myHeight/1.5f
#define GRAVITY PLAYER_SPEED * 3.5f
#define BACKGROUND_LOOP_SPEED myWidth/10.0f
#define OBSTACLE_SPEED PLAYER_SPEED/2.0f
#define DISTANCE_BETWEEN_OBSTACLES myWidth/2.5f

#define ROTATION_SPEED 150.0f

#define FLASH_TIME 0.1f

typedef unsigned short ushort;
extern ushort myWidth, myHeight;