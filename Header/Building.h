/*
 * Building.h
 *
 *  Created on: Oct 26, 2016
 *      Author: Kyle Lavorato
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define SSTR( x ) static_cast< ostringstream & >( \
        ( ostringstream() << dec << x ) ).str()

using namespace std;

class Building {
// This class will never be instiantated
public:
	Building(int x, int y);  // Child constructor will set most of the private attributes
	virtual ~Building();  // Virtual destructor to prevent precompiler warnings
	int getCost() const;  // Returns the cost to construct the building
	int getRevenue() const;  // Returns the revenue/tick
	int getHappiness() const;  // Returns the happiness that the building generates per tick
	int getMaintenance() const;  // Returns the current maintenance cost
	int getMaintenanceTick() const;  // Returns how often maintenance occurs
	int getBuildTime() const;  // The total number of turns to construct the building
	int getRemainingBuildTime() const;  // The number of turns until construction is complete
	int getConstruct() const;  // Returns the integer percentage of construction
	string getType() const;  // Returns the type of the building; String same as class name
	bool getDestroy() const;  // Returns true if the building is marked to be destroyed
	int getX() const;  // Returns the xPosition attribute
	int getY() const;  // Returns the yPosition attribute
	int demolish();  // Demolishes the building and returns the sell profits
	virtual int returnAbstract() const = 0;  // Abstract method to prevent Building from being instantiable
	int updateMoney();  // Increases construction or calculates the revenue/maintenance and returns change in money
	int updateHappiness();  // Returns the happiness per turn generation of the building when apprpriate
	vector<string>& getInfo();  // Returns a vector with all the building info

protected:
	int construct;  // Construction percentage; Is fully constructed and functional at 100
	int cost;  // The cost of the building
	int revenue;  // The amount of money the building generates each tick; Can be 0
	int happiness;  // The amount of happiness that the building generates each tick; Can be 0
	double decay;  // The proportion of currentTick that decreases the sell cost due to old age; 1+decay to increase maintenance
	double sellPercent;  // The percentage of purchase price that the building can be sold for
	double buildPercent;  // The percentage of construction the at building advances each tick
	double maintenancePercent;  // The maintenance cost each occurrence (Percent of revenue)
	int maintenanceTick;  // How often the maintenance cost occurs
	int currentTick;  // How long the building has existed
	int xLocation;  // Where on the map horizontally the building's centre is
	int yLocation;  // Where on the map vertically the building's centre is
	string text;  // Flavour text for the building
	string buildType;  // Type of building; Same as class name
	bool destroy;  // Boolean to mark the building to be destroyed (true to be destroyed)
	vector<string> info;  // Holds the base information for the building in string elements

friend ostream& operator<<(ostream& out, const Building& value);  // Output stream overload for Buildings; Prints the menu info of the building
};  // end Building class

class Lecture : public Building {
public:
	Lecture(int x, int y);  // Construct the building at the supplied x and y positions
	~Lecture();  // Virtual destructor to prevent precompiler warnings
	virtual int returnAbstract() const override;  // Define the method to return the image of the building
};  // end Lecture class

class Lab : public Building {
public:
	Lab(int x, int y);  // Construct the building at the supplied x and y positions
	~Lab();  // Virtual destructor to prevent precompiler warnings
	virtual int returnAbstract() const override;  // Define the method to return the image of the building
};  // end Lab class

class Library : public Building {
public:
	Library(int x, int y);  // Construct the building at the supplied x and y positions
	~Library();  // Virtual destructor to prevent precompiler warnings
	virtual int returnAbstract() const override;  // Define the method to return the image of the building
};  // end Library class

class Residence : public Building {
public:
	Residence(int x, int y);  // Construct the building at the supplied x and y positions
	~Residence();  // Virtual destructor to prevent precompiler warnings
	virtual int returnAbstract() const override;  // Define the method to return the image of the building
};  // end Residence class
