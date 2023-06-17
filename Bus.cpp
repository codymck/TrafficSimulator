#include "Bus.h"

/* Bus constructor taking the location vector of vector of place pointers */
Bus::Bus(vector<vector<Place*>> location) : Vehicle(location)
{
	bus_type = busType[rand() % 2]; //(sizeof(busType) / sizeof(busType[0]))];
}

/* Bus deconstructor */
Bus::~Bus()
{
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = NULL;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = NULL;
	}
}

/* passenger getter and setter */
void Bus::setPassengers(int p)
{
	passengers = p;
}
int Bus::getPassengers()
{
	return passengers;
}

/* get the type of bus */
string Bus::getType()
{
	return bus_type;
}

/* directional movement methods */
void Bus::move_North(int y, int x)
{
	// check for the previous positions behind bus and set to NULL
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = NULL;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = NULL;
	}
	// move front of the bus North
	Vehicle::move_North(y, x);
	location[y2][x2]->position = this;
	// move the last 2 cells of the bus to the next place
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
}

void Bus::move_South(int y, int x)
{
	// check for the previous positions behind bus and set to NULL
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = NULL;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = NULL;
	}
	// move front of the bus South
	Vehicle::move_South(y, x);
	location[y2][x2]->position = this;
	// move the last 2 cells of the bus to the next place
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
}

void Bus::move_East(int y, int x)
{
	// check for the previous positions behind bus and set to NULL
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = NULL;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = NULL;
	}
	// move front of the bus East
	Vehicle::move_East(y, x);
	location[y2][x2]->position = this;
	// move the last 2 cells of the bus to the next place
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
}

void Bus::move_West(int y, int x)
{
	// check for the previous positions behind bus and set to NULL
	if (location[y2][x2] != NULL)
	{
		location[y2][x2]->position = NULL;
	}
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = NULL;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = NULL;
	}
	// move front of the bus West
	Vehicle::move_West(y, x);
	location[y2][x2]->position = this;
	// move the last 2 cells of the bus to the next place
	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
}