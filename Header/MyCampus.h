#ifndef MYCAMPUS_H
#define MYCAMPUS_H

#pragma once
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "../Header/Building.h"
#include "../Header/map.h"
// class attributes of num of each type of building
using namespace std;

class MyCampus {
public:
  MyCampus(int p, float m, float r, ALLEGRO_DISPLAY *ad);
  int getRating();
  int getBuildingRating();
  //void  setRating(float n);
  void  setRating(float n);
  float getMoney();
  void setMoney(int n);
  //void setMoney(float n);
  int getNumProfs();
  void setNumProfs(int n);
  int getPop();
  void setPop(float p);
  void setPop(int n);
  int getMaxPop();
  int getRevenue();
  void addBuilding(Building *b);
  int removeBuilding(int xVal, int yVal); //remove building by iterating coordinates and do nothing if no match
//  vector<int> getBuildingNums();
  bool ifBuildingSpotFree(int x, int y);
  void updateMap();
  int getTurnNumber();
  void nextTurn();


protected:
	float rating; // this will represent the student satisfaction levels, or "happiness ratings"
	float money; // math models will likely output float values, rather than integers
	int population;
	int turn;
  vector<Building*> *buildingList;
  int labs;
  int libs;
  int lecs;
  int res;
  int numProfs;
  Map *m;
  int getMaxPop(int lab, int lib, int lec, int res);

friend ostream& operator<<(ostream& out, const MyCampus& value);  // Output stream overload for MyCampus, prints basic attributes of campus

};

#endif
