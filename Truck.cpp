#include "Truck.h"

/* constructor */
Truck::Truck(vector<vector<Place*>> location) : Vehicle(location)
{
	srand(time(NULL));
	this->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
}
/* deconstructor */
Truck::~Truck()
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
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = NULL;
	}
}

/* getter and setter for cargo */
void Truck::setCargo(double c)
{
	cargo = c;
}
double Truck::getCargo()
{
	return cargo;
}

/* get combined weight of cargo and vehicle weight */
double Truck::getWeight()
{
	return Vehicle::getWeight() + cargo;
}

/* 4 directional movement methods */
void Truck::move_North(int y, int x)
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
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = NULL;
	}

	Vehicle::move_North(y, x);
	location[y2][x2]->position = this;

	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = this;
	}
}
void Truck::move_South(int y, int x)
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
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = NULL;
	}

	Vehicle::move_South(y, x);
	location[y2][x2]->position = this;

	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = this;
	}
}
void Truck::move_East(int y, int x)
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
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = NULL;
	}

	Vehicle::move_East(y, x);
	location[y2][x2]->position = this;

	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = this;
	}
}
void Truck::move_West(int y, int x)
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
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = NULL;
	}

	Vehicle::move_West(y, x);
	location[y2][x2]->position = this;

	if (location[y3][x3] != NULL)
	{
		location[y3][x3]->position = this;
	}
	if (location[y4][x4] != NULL)
	{
		location[y4][x4]->position = this;
	}
	if (location[y5][x5] != NULL)
	{
		location[y5][x5]->position = this;
	}
}