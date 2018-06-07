/*
 *  Events.h
 *
 *  Created on: Nov 1, 2016
 *  Author: Danielle Tremblay
 */

#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Events {
public:
	Events();
	string getEvent();
	int getMoney();
	float getPopulation();
	int getRating();

private:
	//int randomNumberPositiveEvent();
	//int randomNumberNegativeEvent();
	void readPositive();
	void readNegative();
	void readPMoney();
	void readNMoney();
	void readPPopulation();
	void readNPopulation();
	void readPRating();
	void readNRating();
	vector<string> positiveArray, negativeArray;
	vector<int> positiveMoney, 
				negativeMoney, 
				positiveRating, 
				negativeRating, 
				positivePopulation, 
				negativePopulation;
	//Vectors containing all used numbers
	vector<int> usedPositive, usedNegative;
	int money;
	int population;
	int rating;
	string eventString;
};

class FileException {
public:
	FileException(const string& message);
	string& what();

private:
	string message;
};


