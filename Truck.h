#pragma once
#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle
{
private:
	string color;
	double cargo;
public:
	Truck(vector<vector<Place*>> location);
	~Truck();

	/* getters and setters for truck cargo weight and combined weight and vehicle weight */
	void setCargo(double c);
	double getCargo(); 
	double getWeight();

	/* 4 movement directional methods */
	void move_North(int y, int x);
	void move_South(int y, int x);
	void move_East(int y, int x);
	void move_West(int y, int x);
};
#endif