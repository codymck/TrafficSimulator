#include "Place.h"

/* Place constructor */
Place::Place()
{
	north = 0;
	south = 0;
	east = 0;
	west = 0;

	intersection = 0;

	position = NULL;
}

/* Place deconstructor */
Place::~Place()
{
	if (position != NULL)
	{
		delete position;
	}
	position = NULL;
}