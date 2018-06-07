/*
* MyCampus.cpp
* November 16th, 2016
* Christina Yan
*/

#include "../Header/MyCampus.h"
MyCampus::MyCampus(int p, float mo, float r, ALLEGRO_DISPLAY * ad): population(p), money(mo), rating(r), turn(0)
{
  buildingList = new vector<Building*>();
  labs = 0;
  libs = 0;
  res = 0;
  lecs = 0;
  numProfs = 0;
  m = new Map(ad);

}

void MyCampus::setNumProfs(int n){
  numProfs = n;
}

int MyCampus::getNumProfs(){
  return numProfs;
}

int MyCampus::getBuildingRating(){
  int hap = 0;
//  for (Building * b : *buildingList) {
//    hap += b->updateHappiness();
//  }
for (int i = 0; i < buildingList->size(); i++)
    {
    hap += (*buildingList)[i]->updateHappiness();
    }
  return hap;
}

int MyCampus::getRating() {
	return rating;
}

void MyCampus::setRating(float n) {
  rating = n;
}

float MyCampus::getMoney(){
  cout << buildingList->size() << endl;
  return money;
}

void MyCampus::setMoney(int n) {
  money = n;
}

//void MyCampus::setMoney(float n) {
//  float percent = n/100;
//  money *= percent;
//}

void MyCampus::addBuilding(Building *b){
  buildingList->push_back(b);
cout << "pushed" << endl;
  string buildType = b->getType();
  if (buildType == "Lab")
    labs++;
  else if (buildType == "Library")
    libs++;
  else if (buildType == "Residence")
    res++;
  else if (buildType == "Lecture")
    lecs++;
}

int MyCampus::removeBuilding(int xCoord, int yCoord) {
  int index = 0;
  int cost;
  for (Building * b : *buildingList) {
    int b_x = b->getX();
    int b_y = b->getY();
    if (b_x == xCoord && b_y == yCoord) {
      string buildType = b->getType();
      cost = b->demolish();
      if (buildType == "Lab")
        labs--;
      else if (buildType == "Library")
        libs;
      else if (buildType == "Residence")
        res--;
      else if (buildType == "Lecture")
        lecs--;
      break;
    } //end if
    index++;
  }
  buildingList->erase(buildingList->begin() +index);
  return cost;
}
/*
vector<int> MyCampus::getBuildingNums() {
  int numLabs = getLabs();
  int numLibs = getLibs();
  int numRes = getRes();
  int numLecs = getLecs();
  vector<int> *counts = new vector<int>();
  counts = {numLabs, numLibs, numRes, numLecs};
  return counts;
}*/

int MyCampus::getPop() {
  return population;
}

void MyCampus::setPop(int n){
  population = n;
}

// make sure this gets rounded to whole number int
void MyCampus::setPop(float percent){
  population *= percent;
}

//overload to update population based on how many of each type of building we have
int MyCampus::getMaxPop(int lab, int lib, int lec, int res){
  int maxPop = 0;
  maxPop += lab * 130;
  maxPop += lib * 0;
  maxPop += lec * 150;
  maxPop += res * 350;
  return maxPop;
}

// get max pop method
int MyCampus::getMaxPop(){
  int retPop = getMaxPop(labs, libs, lecs, res);
  return retPop;
}

void MyCampus::updateMap(){
  m->updateMap(buildingList);
}

bool MyCampus::ifBuildingSpotFree(int x, int y) {
  for (Building * b : *buildingList) {
    int b_x = b->getX();
    int b_y = b->getY();
    if (b_x == x && b_y == y) {
	cout << "not free" << endl;
      return false;
    } //end if
  }
	cout << "free" << endl;
  return true;
}

int MyCampus::getRevenue() {
  int rev = 0;
  for (Building * b : *buildingList) {
    rev += b->updateMoney();
  }
  return rev;
}

int MyCampus::getTurnNumber() {
  return turn;
}

void MyCampus::nextTurn() {
  turn++;
}



