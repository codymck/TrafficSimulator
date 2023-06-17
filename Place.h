#pragma once
#ifndef PLACE_H
#define PLACE_H

#include <stdlib.h>

class Vehicle;

class Place
{
public:
	Place();
	~Place();

	Vehicle* position;

	bool north, south, east, west;

	bool intersection;
};
#endif 
