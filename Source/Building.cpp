/*
 * Building.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: Kyle
 */

#include "../Header/Building.h"
#include <math.h>
#include <string>
#include <vector>

using namespace std;

Building::Building(int x, int y) {
	// Declare only values that will be constant for all building types
	construct = 0;
	sellPercent = 0.75;
	currentTick = 0;
	decay = 0.02;  // Will result in 0.6 extra in 10 years
	maintenanceTick = 3;  // Annual maintenance
	xLocation = x;
	yLocation = y;
	destroy = false;
}  // end Building()

Building::~Building() { }  // end ~Building()

int Building::getCost() const {
	return cost;
}  // end getCost()

int Building::getRevenue() const {
	return revenue;
}  // end getRevenue()

int Building::getHappiness() const {
	return happiness;
}  // end getHappiness()

int Building::getMaintenance() const {
    int value;
    if (currentTick == 0 && revenue == 0)
        value = round(maintenancePercent / 5 * cost);  // Maintenance is based off of cost / 5
    else if (currentTick == 0)
        value = round(maintenancePercent * revenue);  // Calculate base maintenance
    else if (revenue == 0)
        value = round(maintenancePercent / 5 * cost * (1 + decay * currentTick));
    else
        value = round((maintenancePercent * revenue) * (1 + decay * currentTick));  // Calculate maintenance with decay
	return value;
}  // end getMaintenance()

int Building::getMaintenanceTick() const {
	return maintenanceTick;
}  // end getMaintenanceTick

int Building::getBuildTime() const {
	return round(100 / (buildPercent * 100));
}  // end getBuildTime()

int Building::getRemainingBuildTime() const {
	int totalTicks = getBuildTime();
	totalTicks -= currentTick;
	return totalTicks;
}  // end getRemainingBuildTime()

int Building::getConstruct() const {
	return construct;
}  // end getConstruct()

string Building::getType() const {
    return buildType;
}  // end getType()

bool Building::getDestroy() const {
    return destroy;
}  // end getDestroy()

int Building::getX() const {
	return xLocation;
}  // end getX()

int Building::getY() const {
	return yLocation;
}  // end getY()

int Building::demolish() {
	// CODE TO KNOCK THIS BITCH DOWN //
	destroy = true;
    int sell;
    int unconstructedVal = ((100 - construct) * cost / 100);
    int demolishReturn = round((sellPercent * (cost - unconstructedVal)) - (sellPercent * cost * decay * currentTick)); // Refund unspent money - spent money reduced by decay
    if(construct < 100)
        sell = unconstructedVal + demolishReturn;  // Refund of non-used cash + normal demolish rev
    else
        sell = demolishReturn;  // Recover a fraction of the purchase price with a decay factor
	return sell;
}  // end demolish()

int Building::updateMoney() {
	int profit = 0;  // The amount that the player's money must be adjusted by for this tick
	if (construct >= 100) {
		if(currentTick % maintenanceTick == 0) {  // If maintenance should occur
			profit -= getMaintenance();  // Charge for maintenance with a decay factor
		}
		profit += revenue;  // Add the building's revenue
	}
	else {
		construct += buildPercent * 100;  // Construct a fraction of the building
		profit -= round(cost * buildPercent);  // Charge for a fraction of the construction cost
		if(construct > 100)
			construct = 100;
	}
	currentTick++;
	return profit;
}  // end updateMoney()

int Building::updateHappiness() {
	if (construct >= 100)
		return happiness;  // Only return happiness if building is constructed
	return 0;
}  // end updateHappiness()

vector<string>& Building::getInfo() {
    if (info.size() == 0) {
        int maintCost = maintenancePercent * revenue;
        int sellVal = sellPercent * cost;
        string line;
        if (revenue > 0 && happiness > 0) {
            info.push_back(text);
            line = "Cost: " + SSTR(cost);
            info.push_back(line);
            line = "Revenue: " + SSTR(revenue)+"/turn";
            info.push_back(line);
            line = "Happiness: " + SSTR(happiness) + "/turn";
            info.push_back(line);
            line = "Turns to Construct: " + SSTR(getBuildTime());
            info.push_back(line);
            line = "Maintenance Cost: " + SSTR(maintCost) + " * (" + SSTR(decay + 1) + " per turn)/" + SSTR(maintenanceTick) + " turns";
            info.push_back(line);
            line = "Sell Value: " + SSTR(sellVal) + " * (" + SSTR(decay) + " per turn)";
            info.push_back(line);
        } else if (revenue > 0 && happiness == 0) {
            info.push_back(text);
            line = "Cost: " + SSTR(cost);
            info.push_back(line);
            line = "Revenue: " + SSTR(revenue) + "/turn";
            info.push_back(line);
            line = "Turns to Construct: " + SSTR(getBuildTime());
            info.push_back(line);
            line = "Maintenance Cost: " + SSTR(maintCost) + " * (" + SSTR(decay + 1) + " per turn)/" + SSTR(maintenanceTick) + " turns";
            info.push_back(line);
            line = "Sell Value: " + SSTR(sellVal) + " * (" + SSTR(decay) + " per turn)";
            info.push_back(line);
        } else {
            info.push_back(text);
            line = "Cost: " + SSTR(cost);
            info.push_back(line);
            line = "Turns to Construct: " + SSTR(getBuildTime());
            info.push_back(line);
            line = "Maintenance Cost: " + SSTR(maintCost) + " * (" + SSTR(decay + 1) + " per turn)/" + SSTR(maintenanceTick) + " turns";
            info.push_back(line);
            line = "Sell Value: " + SSTR(sellVal) + " * (" + SSTR(decay) + " per turn)";
            info.push_back(line);
        }
    }
	return info;
}

ostream& operator<<(ostream& out, const Building& value) {
	int maintCost = value.maintenancePercent * value.revenue;
	int sellVal = value.sellPercent * value.cost;
	if (value.revenue > 0 && value.happiness > 0) {
		out << value.text << endl << "Cost: " << value.cost << endl << "Revenue: " << value.revenue << "/turn"
				<< endl << "Happiness: " << value.happiness << "/turn" << endl << "Turns to Construct: "
				<< value.getBuildTime() << endl << "Maintenance Cost: " << maintCost << " * (" << value.decay + 1
				<< " per turn)/" << value.maintenanceTick << " turns" << endl << "Sell Value: " << sellVal << " * ("
				<< value.decay << " per turn)" << endl;
	} else if (value.revenue > 0 && value.happiness == 0) {
		out << value.text << endl << "Cost: " << value.cost << endl << "Revenue: " << value.revenue << "/turn" << endl
				<< "Turns to Construct: " << value.getBuildTime()
				<< endl << "Maintenance Cost: " << maintCost << " * (" << value.decay + 1 << " per turn)/"
				<< value.maintenanceTick << " turns" << endl << "Sell Value: " << sellVal << " * ("
				<< value.decay << " per turn)" << endl;
	} else {
		out << value.text << endl << "Cost: " << value.cost << endl << "Happiness: "
				<< value.happiness << "/turn" << endl << "Turns to Construct: " << value.getBuildTime()
				<< endl << "Maintenance Cost: " << maintCost << " * (" << value.decay + 1 << " per turn)/"
				<< value.maintenanceTick << " turns" << endl << "Sell Value: " << sellVal << " * ("
				<< value.decay << " per turn)" << endl;
	}
	return out;
}  // end operator<< overload


///// Lecture /////
Lecture::Lecture(int x, int y) : Building(x, y){
	cost = 3000;
	revenue = 300;
	happiness = 3;
	buildPercent = 0.34;  // Build in 3 turns
	maintenancePercent = 0.15;  // Lecture halls are low maintenance
	text = "Lecture halls are great for making money, but they don't make students happy.";
	buildType = "Lecture";
}  // end Lecture()

Lecture::~Lecture() { } // end ~Lecture()

int Lecture::returnAbstract() const {
	return 0;
}


///// Lab /////
Lab::Lab(int x, int y) : Building(x, y){
	cost = 7500;
	revenue = 500;
	happiness = 5;
	buildPercent = 0.20;  // Build in 5 turns
	maintenancePercent = 0.45;  // Lab are high maintenance
	text = "Labs bring in research money and students like doing work in them.";
	buildType = "Lab";
}  // end Lab()

Lab::~Lab() { } // end ~Lab()

int Lab::returnAbstract() const {
	return 0;
}


///// Library /////
Library::Library(int x, int y) : Building(x, y){
	cost = 5000;
	revenue = 100;
	happiness = 15;
	buildPercent = 0.10;  // Build in 10 turns
	maintenancePercent = 5.25;  // Libraries are low maintenance
	text = "Libraries make no money, but make the students happy with their services.";
	buildType = "Library";
}  // end Library()

Library::~Library() { } // end ~Library()

int Library::returnAbstract() const {
	return 0;
}



///// Residence /////
Residence::Residence(int x, int y) : Building(x, y){
	cost = 6000;
	revenue = 300;
	happiness = 5;
	buildPercent = 0.25;  // Build in 4 turns
	maintenancePercent = 0.35;  // Residences are high maintenance
	text = "Give students a place to live so they can attend your university.";
	buildType = "Residence";
}  // end Residence()

Residence::~Residence() { } // end ~Residence()

int Residence::returnAbstract() const {
	return 0;
}
