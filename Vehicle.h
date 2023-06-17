#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>

#include "Place.h"
#include "CarColors.h"

using namespace std;

class Vehicle
{
protected:
	vector<vector<Place*>> location;
private:
	int speed;
	double weight;

public:
	/* coordinates */
	int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;

	/* 2D vector of Places */
	Vehicle(vector<vector<Place*>>& location);

	/* setters */
	void setSpeed(int speed);
	void setWeight(double weight);

	/* getters */
	int getSpeed();
	double getWeight();

	/* virtual vehicle deconstructor */
	virtual ~Vehicle();

	/* direction getter / setter */
	char getDirection();
	void setDirection(char direction);
	/* destination getter / setter */
	char getDestination();
	void setDestination(char destination);

	/* direction destination characters */
	char direction;
	char destination;
	/* determine if a vehicle is on the move */
	bool isMoving;

	/* Vehicle movement for each direction */
	virtual void move_North(int y, int x);
	virtual void move_South(int y, int x);
	virtual void move_East(int y, int x);
	virtual void move_West(int y, int x);
};
#endif
