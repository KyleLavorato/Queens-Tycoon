/**
 *  @file    dealer.cpp
 *  @author  Yunshan Richard Yan (13yy29)
 *  @date    Nov 09, 2016
 *  @version 1.0
 *
 *  @brief CMPE 320, team turing, dealer interface
 *
 *  @section DESCRIPTION
 *
 *  This is the implementation for the dealer
 *  interface.
 *
 */

#include "../Header/dealer.h"
#include <cmath>

#define PI 3.14159265

Dealer::Dealer(ALLEGRO_DISPLAY * dis) {
    srand (time(NULL));
    _campus = new MyCampus(0, 40000, 100, dis);
    cout<<"created campus"<<endl;
    try {
    _event = new Events();
    } catch(FileException &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"created events"<<endl;
    _building = 0;
    cout<<"created building"<<endl;
    _status = 0;
    // possiblely use the parameterized constructor...

}

Dealer::~Dealer() {
    delete _campus;
    delete _event;
}

int Dealer::money() {
    return _campus->getMoney();
}

int Dealer::happyness() {
    return _campus->getRating();
}

int Dealer::turnNumber() {
    return _campus->getTurnNumber();
}

int Dealer::num_prof() {
    return _campus->getNumProfs();
}

int Dealer::num_student() {
    return _campus->getPop();
}

std::string Dealer::display_string() {
    return _eventS;
}

void Dealer::updateMap() {
    _campus->updateMap();
}

unsigned int Dealer::status() {
    cout << _status << endl;
    return _status;
}

void Dealer::clickButton(int id) {
    switch (id) {
    case TURN_BUTTON_ID:{
        this->nextTurn();
        break;}
    case ARROW_L_ID:
        _building += 1;
        break;
    case ARROW_R_ID:{
        _building -= 1;
        break;}
    case BUY_PROF_ID:{
        int money = _campus->getMoney();
        money -= PROF_COST;
        if (money < 0) return;
        _campus->setNumProfs(_campus->getNumProfs() + 1);
        _campus->setMoney(money);
        break;}
    case SELL_PROFS_ID:{
        int numProf = _campus->getNumProfs();
        numProf--;
        if (numProf < 0) return;
        _campus->setNumProfs(numProf);
        _campus->setMoney(_campus->getMoney() + PROF_COST);
        break;}
    case BUY_STUDENT_ID:{
    }
    case SELL_STUDENT_ID:{
    }
    }

    if(_building == 4) _building = 0;
    else if (_building == -1) _building = 3;
	switch(_building) {
		case 0:
		_cost = 3000;
		break;
		case 1:
		_cost = 7500;
		break;
		case 2:
		_cost = 5000;
		break;
		case 3:
		_cost = 6000;
		break;
 	}
}

void Dealer::nextTurn() {
    if (_status & (1 << STAT_WIN | 1 << STAT_LOSE)) {
        return; // do not proceed if already win or lose
    }

    // _campus->getStat() += _campus-> getAggregatedDelta();
    // assuming getStat() returns a reference, otherwise use setter

    // chech _campus->getStat() to see if lose or win
    // set up relevent bit in status
    // and return
    int pop = _campus->getPop();
    int maxPop = _campus->getMaxPop();
    _campus->setPop((int)(pop + (maxPop - pop) * 0.1 * (_campus->getRating() - 50) / 100.0));
    if (_campus->getPop() <0) _campus->setPop(0);
	float rate;
	if (_campus->getPop() == 0) rate = 100;
	else{
        rate = atan(_campus->getNumProfs() / (_campus->getPop() / 100.0));
	rate -= PI * 0.25;
	rate *=2;
	rate += 0.5*PI;
	rate /= PI;
	rate *= 100;
	rate += _campus->getBuildingRating() * 0.1;}
        if (rate < 0) rate = 0;
        if (rate > 100) rate = 100;
        _campus->setRating(rate);
	int money = _campus->getMoney() + _campus->getRevenue() + _campus->getPop() * 0.1 - _campus->getNumProfs() * 100;
	_campus->setMoney(money);

    if (rand() * 1.0 / RAND_MAX > 0.5) {
        _eventS = _event->getEvent();
        int pop = _campus->getPop() - _event->getPopulation();
        if (pop < 0) pop = 0;
        _campus->setPop(pop);
        int rate = _campus->getRating() - _event->getRating();
        if (rate < 0) rate = 0;
        if (rate > 100) rate = 100;
        _campus->setRating(rate);
        int money = _campus->getMoney() - _event->getMoney();
        if (money < 0) money = 0;
        _campus->setMoney(money);
    }
    else _eventS = "";

    _campus->nextTurn();
    if (_campus->getTurnNumber() >= 150) {
        _status = 1 << STAT_WIN;
	cout << "status:" << _status << endl;
        return;
    }
    else if (_campus->getMoney() < 0) {
        _status = 1 << STAT_LOSE;
	cout << "status:" << _status << endl;
        return;
    }

    updateMap();
}

void Dealer::mouseClick(unsigned x, unsigned y, int state) {
    x /= 50;
    y /= 50;

    if (state == LEFT_CLICK)
        {placeBuilding(x,y);
        cout << "placed" << endl;}
    else
        {deleteBuilding(x,y);
        cout << "deleted" << endl;
        }
}

void Dealer::placeBuilding(unsigned int x, unsigned int y) {
	cout << "trying at " << x << " " << y << endl;
    if (!_campus->ifBuildingSpotFree(x, y))
        return;

	cout << "ok" << endl;

    Building *bld;
    switch (_building) {
    case 0:
        bld = new Lecture(x ,y);
	cout << "lec" << endl;
        break;
    case 1:
        bld = new Lab(x ,y);
	cout << "lab" << endl;
        break;
    case 2:
        bld = new Library(x ,y);
	cout << "lib" << endl;
        break;
    case 3:
        bld = new Residence(x ,y);
	cout << "res" << endl;
        break;
    }

	cout << "money: " << _campus->getMoney() << " cost: " << bld->getCost() << endl;
    if (_campus->getMoney() > bld->getCost()) {
	cout << "adding" << endl;
        _campus->addBuilding(bld);
        _campus->setMoney(_campus->getMoney() - bld->getCost());
        cout << "money: " << _campus->getMoney() << endl;
    }
cout << "done" << endl;
}

void Dealer::deleteBuilding(unsigned int x, unsigned int y) {
    if (_campus->ifBuildingSpotFree(x, y))
        return;

    _campus->setMoney(_campus->getMoney() + _campus->removeBuilding(x, y));
}
