#include "../Header/GUI.h"
#include "../Header/Building.h"
using namespace std;

void Game::buttonCheck(int x, int y)
{
    if ( x > QUIT_X && x < QUIT_X + BUTTON_W && y > QUIT_Y && y < QUIT_Y + BUTTON_H) //exit
    {
        al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        exit(0);
    }
    else if ( x > TURN_X && x < TURN_X + BUTTON_W && y > TURN_Y && y < TURN_Y + BUTTON_H) // turn
    {
        al_play_sample(turnSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        myHandler->clickButton(TURN_BUTTON_ID);
    }
    else if ( x > ARROW_L_X && x < ARROW_L_X + ARROW_W && y > ARROW_Y && y < ARROW_Y + ARROW_H) //arrow L
    {
        al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        myHandler->clickButton(ARROW_L_ID);
    }
     else if ( x > ARROW_R_X && x < ARROW_R_X + ARROW_W && y > ARROW_Y && y < ARROW_Y + ARROW_H) //arrow R
    {
        al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        myHandler->clickButton(ARROW_R_ID);
    }
    else if ( x > BUYSELL_X && x < BUYSELL_X+ BUTTON_W && y > BUTTON_2_Y && y < BUTTON_2_Y + BUTTON_H) //buy1
    {
        al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        myHandler->clickButton(BUY_PROF_ID);
    }
   else if ( x > BUYSELL_X && x < BUYSELL_X+ BUTTON_W && y > BUTTON_3_Y && y < BUTTON_3_Y + BUTTON_H) //sell 1
    {
        al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        myHandler->clickButton(SELL_PROFS_ID);
    }
   //else if ( x > BUYSELL_X && x < BUYSELL_X + BUTTON_W && y > BUTTON_4_Y && y < BUTTON_4_Y + BUTTON_H) //buy2
    //{
   //     al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    //    myHandler->clickButton(BUY_STUDENT_ID);
    //}
   //else if ( x > BUYSELL_X && x < BUYSELL_X+ BUTTON_W && y > BUTTON_5_Y && y < BUTTON_5_Y + BUTTON_H) // sell 2
    //{
    //    al_play_sample(buttonSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    //    myHandler->clickButton(SELL_STUDENT_ID);
    //}
}

void Game::reDraw ()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(UI,0,0,0);
    al_draw_bitmap(leftArrow,ARROW_L_X,ARROW_Y,0);
    al_draw_bitmap(rightArrow,ARROW_R_X,ARROW_Y,0);
    al_draw_bitmap(turn, TURN_X, TURN_Y,0);
    al_draw_bitmap(quit, QUIT_X,QUIT_Y,0);
    al_draw_bitmap(buyButton, BUYSELL_X, BUTTON_2_Y,0);
    al_draw_bitmap(sellButton, BUYSELL_X, BUTTON_3_Y,0);
    //al_draw_bitmap(buyButton, BUYSELL_X, BUTTON_4_Y,0);
    //al_draw_bitmap(sellButton, BUYSELL_X, BUTTON_5_Y,0);
    int b = myHandler->_building;
    int co = myHandler->_cost;

    if (b==0)
        al_draw_bitmap(b0, (ARROW_L_X + ARROW_R_X)/2, ARROW_Y,0);
    if (b==3)
        al_draw_bitmap(b1, (ARROW_L_X + ARROW_R_X)/2, ARROW_Y,0);
    if (b==1)
        al_draw_bitmap(b2, (ARROW_L_X + ARROW_R_X)/2, ARROW_Y,0);
    if (b==2)
        al_draw_bitmap(b3, (ARROW_L_X + ARROW_R_X)/2, ARROW_Y,0);


    //look in repo and fix this
    string me = myHandler->display_string();
    if (me.length() == 0)
    {
        message = "A relaxing, boring semester unfolds.";
    }
    else
        message = me;

    int happ = myHandler->happyness();
    int money = myHandler->money();
    int profs = myHandler->num_prof();
    int students = myHandler->num_student();
    int turn = myHandler->turnNumber();

    string h = SSTR(happ);
    const char  *hchar = h.c_str();
    string m = SSTR(money);
    const char  *mchar = m.c_str();
    string p = SSTR(profs);
    const char  *pchar = p.c_str();
    string s = SSTR(students);
    const char *schar = s.c_str();
    string t = SSTR(turn);
    const char *tchar = t.c_str();
    string c = SSTR(co);
    const char *cchar = c.c_str();

    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),HAPPY_X,TEXT_TOP_Y,0,hchar);
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),CASH_X,TEXT_TOP_Y,0,mchar);
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),UNITS_X,NUM_PROFS_Y,0,pchar);
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),UNITS_X +5,NUM_PROFS_Y+60,0,"$500");
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),UNITS_X +5,NUM_PROFS_Y+115,0,"$500");
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),UNITS_X - 60,NUM_STUDENTS_Y +90,0,schar);
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),BOX_TEXT_X +20,BOX_TEXT_Y,0,message.c_str());
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),DATE_X+200,TURN_Y+15,0,tchar);
    al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),DATE_X+50,TURN_Y+15,0,"Semester:");
    //al_draw_text(fontUIMoney,al_map_rgb(0, 0, 0),WHEREE VER I AM PUTTING THE COST,0,cchar);

    myHandler->updateMap();
    al_flip_display();
}

Game::Game()
{
    message = "Welcome! Place your first building!";
}

void Game::mapEvent (int x, int y, int b)
{
    if (b == 1)
    {
        myHandler->mouseClick(x-MAP_X,y-MAP_Y,b);
    }
    else if (b == 2 )
    {
        myHandler->mouseClick(x-MAP_X,y-MAP_Y,b);
    }
}
void Game::startGame()
{

   al_set_new_display_flags(ALLEGRO_FRAMELESS);
    if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
   }

   if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
   }

   display = al_create_display(WINDOW_W,WINDOW_H);
   //al_clear_to_color(al_map_rgb(255, 0, 255));
   al_flip_display();

   if(!display)
   {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
   }

    if(!al_install_audio()){
      al_show_native_message_box(display, "Error", "Error", "Sound error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
   }
   if(!al_init_acodec_addon()){
      al_show_native_message_box(display, "Error", "Error", "Sound error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
   }
   if (!al_reserve_samples(4)){
      al_show_native_message_box(display, "Error", "Error", "Sound error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
   }

   al_init_font_addon();
   al_init_ttf_addon();
   al_init_primitives_addon();
   al_install_mouse();

   fontUITop = al_load_ttf_font("8bit.ttf",22,0 );
   fontUIMoney = al_load_ttf_font("8bit.ttf",16,0 );

   startMusic = al_load_sample( "MenuMusic.ogg" );
   endMusic = al_load_sample("LossMusic.ogg");
   music = al_load_sample( "MainMusic.ogg" );
   buttonSound = al_load_sample("8BitClick.wav");
   turnSound = al_load_sample("TurnEnd.ogg");

   UI = al_load_bitmap("ui.png");
   buyButton = al_load_bitmap("buy.bmp");
   sellButton = al_load_bitmap("sell.bmp");
   leftArrow = al_load_bitmap("arrowL.bmp");
   rightArrow = al_load_bitmap("arrowR.bmp");
   turn = al_load_bitmap("turn.bmp");
   quit = al_load_bitmap("quit.bmp");
   lose = al_load_bitmap("lose.png");
   win = al_load_bitmap("win.png");
   b0 = al_load_bitmap("b0.png");
   b1 = al_load_bitmap("b1.png");
   b2 = al_load_bitmap("b2.png");
   b3 = al_load_bitmap("b3.png");
   instructionsOne = al_load_bitmap("i1.jpg");
   instructionsTwo = al_load_bitmap("i2.jpg");
   splashScreen = al_load_bitmap("splash.bmp");

   myHandler = new Dealer(display);

al_play_sample(startMusic, 0.6, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

ALLEGRO_EVENT_QUEUE *start_queue = al_create_event_queue();
al_register_event_source(start_queue, al_get_mouse_event_source());
al_clear_to_color(al_map_rgb(0, 0, 0));
al_draw_bitmap(splashScreen,0,0,0);
//al_draw_text(fontUIMoney,al_map_rgb(0, 0, 0),503,253,ALLEGRO_ALIGN_CENTRE,"WELCOME TO CAMPUS SIMULATOR");
//al_draw_text(fontUIMoney,al_map_rgb(0, 0, 0),503,328,ALLEGRO_ALIGN_CENTRE,"CLICK TO CONTINUE");
//al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),500,250,ALLEGRO_ALIGN_CENTRE,"WELCOME TO CAMPUS SIMULATOR");
//al_draw_text(fontUIMoney,al_map_rgb(255, 255, 255),500,325,ALLEGRO_ALIGN_CENTRE,"CLICK TO CONTINUE");

al_flip_display();
while (1)
{
ALLEGRO_EVENT ee;
    al_wait_for_event(start_queue, &ee);
    if(ee.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        break;
}
al_draw_bitmap(instructionsOne,0,0,0);
al_flip_display();
while (1)
{
ALLEGRO_EVENT ee;
    al_wait_for_event(start_queue, &ee);
    if(ee.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        break;
}
al_draw_bitmap(instructionsTwo,0,0,0);
al_flip_display();
while (1)
{
ALLEGRO_EVENT ee;
    al_wait_for_event(start_queue, &ee);
    if(ee.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        break;
}

al_stop_samples();

ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
al_register_event_source(event_queue, al_get_mouse_event_source());
unsigned int yy = 0;
reDraw();
al_play_sample(music, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

while (yy == 0)
{
    ALLEGRO_EVENT e;
    al_wait_for_event(event_queue, &e);
    if(e.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        int x = e.mouse.x;
        int y = e.mouse.y;
        int b = e.mouse.button; //1 = left 2 = right

        if ( (x < (MAP_X + MAP_W)) && (x > (MAP_X)) && (y < (MAP_Y + MAP_H)) && (y > MAP_Y))
        {
            mapEvent(x,y,b);
        }

        else
        {
            buttonCheck(x,y);
        }
        reDraw();
        yy = myHandler->status();
        cout << yy << endl;
    }
}
al_stop_samples();
al_clear_to_color(al_map_rgb(255, 255, 255));
al_play_sample(endMusic, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

if (yy==2)
    al_draw_bitmap(lose,0,0,0);
else
    al_draw_bitmap(win,0,0,0);
al_flip_display();

Sleep(5000);
   //Destroy All Bitmaps Afterwards
   al_destroy_display(display);
   al_destroy_bitmap(UI);
   al_destroy_bitmap(buyButton);
   al_destroy_bitmap(sellButton);
   al_destroy_bitmap(leftArrow);
   al_destroy_bitmap(rightArrow);
    //return 0;
}

