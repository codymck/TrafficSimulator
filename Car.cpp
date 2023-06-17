#include "Car.h"

/* Car constructor sets the color of the car */
Car::Car(vector<vector<Place*>> location) : Vehicle(location)
{
	this->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
}
/* deconstructor */
Car::~Car()
{
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}
}

/* getColor() returns the color of the car */
string Car::getColor()
{
	return color;
}

/* directional movement methods */
void Car::move_North(int y, int x)
{
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}

	Vehicle::move_North(y, x);
	location[y2][x2]->position = this;
}
void Car::move_South(int y, int x)
{
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}

	Vehicle::move_South(y, x);
	location[y2][x2]->position = this;
}
void Car::move_East(int y, int x)
{
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}

	Vehicle::move_East(y, x);
	location[y2][x2]->position = this;
}
void Car::move_West(int y, int x)
{
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}

	Vehicle::move_West(y, x);
	location[y2][x2]->position = this;
}