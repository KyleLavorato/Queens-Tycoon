/*
* Map.h
* Nov. 1, 2016
* Mike Kennelly
*/

#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>
#include <vector>
#include "Building.h"

using namespace std;

//Display Constants
const int MAP_W = 815;
const int MAP_H = 365;
const int MAP_X = 17;
const int MAP_Y = 60;
const int NUMROWS = 7;
const int NUMCOLS = 16;
const int BLOCKSIZE = 50;
const int PADDING = 0;

class Map {
public:
    Map(ALLEGRO_DISPLAY*); //Constructor for the map which sets the attributes about its size and position.
    Map(const Map&); //Copy constructor which takes in a Map and makes this a copy.
    ~Map(); //destructor to ensure everything is removed from the heap.
    Map& operator=(const Map&); //Assignment overload operator to set equal to a different Map and reallocate memory properly.
    int** getMap(); //accessor for the map array itself if accessing in the GUI class for some reason.
    void updateMap(vector<Building*> *); //used to modify the map when something is added or removed.
private:
    //void loadMap(const string& filename); //takes in a txt filename to load the data from. as well as the attributes for the position and size of the map and the tile size.
    void drawMap(); //function which draws the map to the screen using allegro library and the gameMap attribute. Adds it to the display which is passed in.
    int getBuildImg(const string&, int);
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* tileSet;
    int** gameMap; //2d array to hold which textures will be mapped to which set of pixels on the display.
};

//class to be thrown when the file can't be loaded properly or the map isn't edited properly
class MapLoadException {
public:
    MapLoadException(const string&); //constructor for the exception itself
    string what() const; //accessor for the message
private:
    string message; //stores the error message string
};
