#pragma once

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#define  ALLEGRO_STATICLINK
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "dealer.h"

//Window Constants
const int WINDOW_H = 500;
const int WINDOW_W = 1000;
const int SYMBOL_W = 50;
const int SYMBOL_H = 50;
const int BUTTON_W = 80;
const int BUTTON_H = 40;
const int ARROW_W = 80;
const int ARROW_H = 80;
const int BUYSELL_X = 842;
//const int MAP_W = 815;
//const int MAP_H = 365;
//const int MAP_X = 20;
//const int MAP_Y = 60;

//Button Placement Constants
const int BUTTON_2_Y = 130;
const int BUTTON_3_Y = 180;
const int BUTTON_4_Y = 315;
const int BUTTON_5_Y = 365;
const int ARROW_Y = 430;
const int ARROW_L_X = 20;
const int ARROW_R_X = 175;
const int CASH_X = 80;
const int HAPPY_X = 300;
const int DATE_X = 430;
const int TEXT_TOP_Y = 20;
const int UNITS_X = 930;
const int NUM_STUDENTS_Y = 260;
const int NUM_PROFS_Y = 80;
const int PRICE_X = 930;
const int PRICE_Y_2 = 142;
const int PRICE_Y_3 = 192;
const int PRICE_Y_4 = 327;
const int PRICE_Y_5 = 377;
const int TURN_X = 745;
const int TURN_Y = 5;
const int QUIT_X = 900;
const int QUIT_Y = 5;
const int BOX_TEXT_X = 300;
const int BOX_TEXT_Y = 450;

class Game
{
public:
Game();
void startGame();
private:
ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *fontUITop;
ALLEGRO_FONT *fontUIMoney;
ALLEGRO_BITMAP *UI;
ALLEGRO_BITMAP *buyButton;
ALLEGRO_BITMAP *sellButton;
ALLEGRO_BITMAP *leftArrow;
ALLEGRO_BITMAP *rightArrow;
ALLEGRO_BITMAP *quit;
ALLEGRO_BITMAP *lose;
ALLEGRO_BITMAP *b0;
ALLEGRO_BITMAP *b1;
ALLEGRO_BITMAP *b2;
ALLEGRO_BITMAP *b3;
ALLEGRO_BITMAP *instructionsOne;
ALLEGRO_BITMAP *instructionsTwo;
ALLEGRO_BITMAP *turn;
ALLEGRO_BITMAP *win;
ALLEGRO_BITMAP *splashScreen;
ALLEGRO_SAMPLE *music;
ALLEGRO_SAMPLE *startMusic;
ALLEGRO_SAMPLE *buttonSound;
ALLEGRO_SAMPLE *turnSound;
ALLEGRO_SAMPLE *endMusic;
std::string message;
Dealer* myHandler;
void reDraw ();
void buttonCheck(int x, int y);
void mapEvent(int x,int y,int b);
};
#endif // GUI_H_INCLUDED
