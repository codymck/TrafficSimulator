#pragma once
#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

static const char* motorcycle_type[] = {
	"Harley",
	"Triumph",
	"Kawasaki",
	"Yamaha"
};

class Motorcycle : public Vehicle
{
public:
	Motorcycle(vector<vector<Place*>> location);
	~Motorcycle();
	string getType();
private:
	string brand;
};
#endif