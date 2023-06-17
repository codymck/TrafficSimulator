#include "Motorcycle.h"

// Motorcycle constructor gives it a random brand type
Motorcycle::Motorcycle(vector<vector<Place*>> location) : Vehicle(location)
{
	brand = motorcycle_type[rand() % (sizeof(motorcycle_type) / sizeof(motorcycle_type[0]))];
}

// Motorcycle deconstructor
Motorcycle::~Motorcycle()
{
	if (location[y1][x1] != NULL)
	{
		location[y1][x1]->position = NULL;
	}
}

// return Motorcycle type
string Motorcycle::getType()
{
	return brand;
}