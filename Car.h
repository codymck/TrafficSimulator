#pragma once
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle
{
private:
	string color;

public:
	/* constructor / deconstructor */
	Car(vector<vector<Place*>> location);
	~Car();

	/* return color */
	string getColor();

	/* directional movement methods */
	void move_North(int y, int x);
	void move_South(int y, int x);
	void move_East(int y, int x);
	void move_West(int y, int x);
};
#endif