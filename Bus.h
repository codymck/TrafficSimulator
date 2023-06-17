#pragma once
#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"

static const char* busType[] = { "School", "MBTA" };

class Bus : public Vehicle
{
private:
	string bus_type;
	int passengers;
public:
	Bus(vector<vector<Place*>> location);
	~Bus();

	void setPassengers(int passengers);
	int getPassengers();

	string getType();

	void move_North(int y, int x);
	void move_South(int y, int x);
	void move_East(int y, int x);
	void move_West(int y, int x);
};
#endif