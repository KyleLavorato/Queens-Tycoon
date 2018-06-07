/*
CISC 320 Team Turing Map Implementation Class

*/

#include "../Header/map.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

//Exception Class declaration
MapLoadException::MapLoadException(const string& message) : message(message) {}
string MapLoadException::what() const {return message;}

//Map Class Declaration
Map::Map(ALLEGRO_DISPLAY* disp) {
    display = disp;
    gameMap = new int*[NUMROWS];
    for (int rows=0;rows<NUMROWS;rows++)
        gameMap[rows] = new int[NUMCOLS];
    //loadMap("basicmap.txt");
    cout<<"test"<<endl;
    tileSet = al_load_bitmap("tileTextures.jpg");
    cout<<"passed"<<endl;
    for (int row = 0; row < NUMROWS; row++){
        for (int col = 0; col<NUMCOLS; col++){
            gameMap[row][col] = 0;
        }
    }
    drawMap();
}
//Copy Constructor also not necessary but included because big three
Map::Map(const Map&){

}
Map::~Map(){
    for(int i=0;i<NUMROWS;i++){
        delete[] gameMap[i];
    }
    delete[] gameMap;
    gameMap = nullptr;
}

//Assignment Overload, not really necessary but big three so here it is.
Map& Map::operator=(const Map&){

}


//DO NOT FLIP THE SCREEN
void Map::drawMap(){
    for (int row = 0; row<NUMROWS; row++){
        for(int col = 0; col<NUMCOLS; col++){
            al_draw_bitmap_region(tileSet, gameMap[row][col]* BLOCKSIZE, 0, BLOCKSIZE, BLOCKSIZE, col*BLOCKSIZE+PADDING+MAP_X, row*BLOCKSIZE+PADDING+MAP_Y, NULL);
        }
    }
}

int** Map::getMap(){
    return gameMap;
}


void Map::updateMap(vector<Building*> *b){
    //First loop through all of the tiles to set them to the baseline.
    for (int row = 0; row<NUMROWS; row++)
    {
        for(int col = 0; col<NUMCOLS; col++){
            al_draw_bitmap_region(tileSet, 0, 0, BLOCKSIZE, BLOCKSIZE, col*BLOCKSIZE+PADDING+MAP_X, row*BLOCKSIZE+PADDING+MAP_Y, NULL);
        }
    }
    //Now loop through building list to see if the tile needs to be changed.
    for (int building=0; building<b->size(); building++){
        Building* build = b->at(building);
        int buildX = build->getX();
        int buildY = build->getY();
        int buildPercent = build->getConstruct();
        string buildType = build->getType();
        cout<<"getting building image"<<endl;
        int buildImg = getBuildImg(buildType, buildPercent);
        cout <<"build type: "<<buildType<<endl<<"build percent: "<<buildPercent<<endl;
        cout<<"got building image:" << buildImg<<endl;
        //gameMap[row][col] = buildImg;
        al_draw_bitmap_region(tileSet, buildImg*BLOCKSIZE, 0, BLOCKSIZE, BLOCKSIZE, buildX*BLOCKSIZE+PADDING+MAP_X, buildY*BLOCKSIZE+PADDING+MAP_Y, NULL);
    }
}

int Map::getBuildImg(const string& type, int percent){
    int index = 0;
    if (type=="Lecture"){
        int pc[4] = {0, 34, 68, 100};
        while (index < 4){
            if (percent == pc[index])
                return index+1; //Return will be in range 1-4
            index++;
        }
    }
    else if (type =="Residence"){
        int pc[5] = {0, 25, 50, 75, 100};
        while (index < 5){
            if (percent == pc[index])
                return index + 5; //return in range 5-9
            index++;
        }
    }
    else if (type =="Lab"){
        int pc[6] = {0, 20, 40, 60, 80, 100};
        while (index < 6){
            if (percent == pc[index]){
                if(percent<=20)
                    return 10;
                else if (percent<=60)
                    return 11;
                else if (percent<=100)
                    return 12;
            }
            index++;
        }
    }
    else { //type == Library
        int pc[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        while (index < 11){
            if (percent == pc[index]){
                if(percent<=20)
                    return 13;
                else if (percent<=50)
                    return 14;
                else if (percent<=80)
                    return 15;
                else
                    return 16;
            }
            index++;
        }
    }

}
/*
res: 4 turns - 25, 50, 75, 100
lab: 5 turns - 20, 40, 60, 80, 100
lec: 3 turns - 34, 68, 100
lib: 10 turns - 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
*/


/*
void Map::loadMap(const string& filename){
    enum LoadState {TileSet, Map};
    int state = NULL;
    int loadCounterRow = 0, loadCounterCol = 0;
    ifstream openFile(filename);
    if(openFile.is_open()){
        string line;
        getline(openFile, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        openFile.seekg(0, ios::beg);
        while(!openFile.eof()){
            if (line.find("[TileSet]") != string::npos){
                state = TileSet;
                continue;
            }
            else if (line.find("[Map]") != string::npos){
                state = Map;
                continue;
            }

            switch(state){
            case TileSet:
                if (line.length() > 0)
                    tileSet = al_load_bitmap(line.c_str());
                break;
            case Map:
                openFile >> gameMap[loadCounterRow][loadCounterCol];
                loadCounterCol++;

                if (loadCounterCol >= NUMCOLS){
                    loadCounterCol = 0;
                    loadCounterRow++;
                }

                break;
            }
        }
    } else {
        throw MapLoadException("Could Not Load Map File!");
    }
}*/
