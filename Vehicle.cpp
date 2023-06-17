#include "Vehicle.h"

/* Vehicle constructor that takes our vector of places and determines a direction / destination */
Vehicle::Vehicle(vector<vector<Place*>>& location)
{
	x1 = y1 = x2 = y2 = x3 = y3 = x4 = y4 = x5 = y5 = 0;

	// give us a random # between 0 - 3 to determine direction
	int d = rand() % 4;

	switch (d)
	{
	case 0:
		direction = 'N';
		break;
	case 1:
		direction = 'S';
		break;
	case 2:
		direction = 'E';
		break;
	case 3:
		direction = 'W';
		break;
	}

	destination = direction;
	
	/* give us a random # to determine a destination that is not our direction
	do
	{
		int de = rand() % 4;
		switch (de)
		{
		case 0:
			destination = 'N';
			break;
		case 1:
			destination = 'S';
			break;
		case 2:
			destination = 'E';
			break;
		case 3:
			destination = 'W';
			break;
		}
	} while (destination = direction); */

	weight = 0;
	speed = 0;

	isMoving = false;

	this->location = location;
}

/* Vehicle deconstructor */
Vehicle::~Vehicle()
{
	if (location[y1][x1] != NULL)
	{
		location[y1][x1]->position = NULL;
	}
}

/* setters for speed and weight */
void Vehicle::setSpeed(int s)
{
	this->speed = s;
}
void Vehicle::setWeight(double w)
{
	this->weight = w;
}

/* getters for weight and speed */
double Vehicle::getWeight()
{
	return weight;
}
int Vehicle::getSpeed()
{
	return speed;
}

/* Direction setter / getter */
void Vehicle::setDirection(char d)
{
	direction = d;
}
char Vehicle::getDirection()
{
	return direction;
}

/* Destination setter / getter */
void Vehicle::setDestination(char d)
{
	destination = d;
}
char Vehicle::getDestination()
{
	return destination;
}

/* North bound movement */
void Vehicle::move_North(int y, int x)
{
	y5 = y4;
	x5 = x4;
	y4 = y3;
	x4 = x3;
	y3 = y2;
	x3 = x2;
	y2 = y;
	x2 = x;
	y1 = y - 1;
	x1 = x;

	// moves the position up one in our location grid
	location[y - 1][x]->position = this;
	location[y][x]->position = NULL;
}

/* South bound movement */
void Vehicle::move_South(int y, int x)
{
	y5 = y4;
	x5 = x4;
	y4 = y3;
	x4 = x3;
	y3 = y2;
	x3 = x2;
	y2 = y;
	x2 = x;
	y1 = y + 1;
	x1 = x;

	// moves the position down one in our location grid
	location[y + 1][x]->position = this;
	location[y][x]->position = NULL;
}

/* East bound movement */
void Vehicle::move_East(int y, int x)
{
	y5 = y4;
	x5 = x4;
	y4 = y3;
	x4 = x3;
	y3 = y2;
	x3 = x2;
	y2 = y;
	x2 = x;
	y1 = y;
	x1 = x + 1;

	// moves the position down one in our location grid
	location[y][x + 1]->position = this;
	location[y][x]->position = NULL;
}

/* West bound movement */
void Vehicle::move_West(int y, int x)
{
	y5 = y4;
	x5 = x4;
	y4 = y3;
	x4 = x3;
	y3 = y2;
	x3 = x2;
	y2 = y;
	x2 = x;
	y1 = y;
	x1 = x - 1;

	// moves the position down one in our location grid
	location[y][x - 1]->position = this;
	location[y][x]->position = NULL;
}