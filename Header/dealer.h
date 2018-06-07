/**
 *  @file    dealer.h
 *  @author  Yunshan Richard Yan (13yy29)
 *  @date    Nov 09, 2016
 *  @version 1.0
 *
 *  @brief CMPE 320, team turing, dealer interface
 *
 *  @section DESCRIPTION
 *
 *  This is the declearation file for the dealer
 *  interface.
 *
 */

#pragma once

#define  ALLEGRO_STATICLINK
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>
#include <cstdlib>
#include "MyCampus.h"
#include "Events.h"

const int TURN_BUTTON_ID = 1;
const int ARROW_L_ID     = 2;
const int ARROW_R_ID     = 3;
const int BUY_PROF_ID    = 4;
const int SELL_PROFS_ID    = 5;
const int BUY_STUDENT_ID    = 6;
const int SELL_STUDENT_ID    = 7;

#define PROF_COST 500

#define STAT_WIN 0
#define STAT_LOSE 1

#define LEFT_CLICK 1
#define RIGHT_CLICK 2


////////////////////////////////////////////////////////////////
// discussion needed yet:
// 1. how to implement buttons?
//  A: Use a function take button id as argument and use switch statement
// 2. how to place a building?
//  A:
// 3. how to represent an event? and how to get response?
////////////////////////////////////////////////////////////////
class Dealer
{
public:
    /**
     * @brief Constructor
     *
     * @details Initialize a game dealer object. Usually there will
     * only be one instance of this class, but it is still recommanded
     * to put the object on the heap.
     *
     * Firstly, the dealer has to instantiate a campus object and keep
     * an reference to it. Then it has to prepare several bitmaps for
     * the menus/tool bars/etc.
     *
     * Since the constructor does not return anything, who using this
     * class has to then call map() to obtain a visual representation
     * of the object for display.
     */
    Dealer(ALLEGRO_DISPLAY * dis);

public:
    /**
     * @brief Destructor
     *
     * @details Automatically called when deleting a dealer object.
     *
     * The object is responsible to delete the campus object and free
     * the bitmaps.
     */
    ~Dealer();

public:
    /**
     * @brief accessor to the money value
     *
     * @details Since this function is only accessing money, there should
     * not be any check here. I cannot see any reason why under any
     * circumstance the value must be kept as a secret from the player.
     *
     * The game rule does allow debt, does not it?
     *
     * max value is 2,147,483,647, two billion that is. Should suffice.
     * In case it does not suffice, use float. DO NOT USE LONG!!!
     *
     * @return an int value for the money
     */
    int money();
    int happyness();
    int turnNumber();
    int num_prof();
    int num_student();
    std::string display_string();
    unsigned int status();

public:
    void updateMap();

public:
    /**
     * @brief click on a button by id
     * @details Allegro somehow determines which button is clicked and call
     * this function with id of the button.
     *
     * perhaps use switch?
     *
     * will likely change depending how we implement buttons.
     *
     * perhaps avaliable building slots on the map can also be implemented as
     * buttons? Simplified a lot.
     *
     * @param id id of the button clicked.
     */
    void clickButton(int id);

private:
    /**
     * @brief proceed to the next turn
     *
     * @details call nextTurn() on campus object. obtain certain status
     * from campus object and check against the rule.
     *
     * Setup flags for indecations if needed.
     *
     * Notes: perhaps return void and let the caller check if lose flag
     * is set? But what if caller ignores and keep calling nextTurn()?
     * could throw an exception?
     */
    void nextTurn();

public:
    void mouseClick(unsigned x, unsigned y, int state);

private:
    /**
     * @brief place currently selected building at specified position
     *
     * position relative to upper-left corner, increases going down/right
     *
     * @param int horizontal position
     * @param int vertical position
     */
    void placeBuilding(unsigned int x, unsigned int y);
    void deleteBuilding(unsigned int x, unsigned int y);

private:
    MyCampus* _campus;

private:
    unsigned int _status;


public:
    /**
     * selected building, perhaps use int id? since there are limited number
     * of choises.
     */
    unsigned int _building;
    int _cost;

private:
    Events* _event;

private:
    string _eventS;

};
