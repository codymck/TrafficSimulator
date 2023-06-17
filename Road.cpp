#include "Road.h"

HANDLE colorOutput = GetStdHandle(STD_OUTPUT_HANDLE);

/* constructor */
Road::Road()
{
	int size = gridSize;
	location.resize(size);		// size our vector to proper length and width

	for (int i = 0; i < location.size(); i++)
	{
		location[i].resize(size);
	}

	size = size / 2;			// middle of our grid size to find intersection

	/* NORTH / SOUTH Bound lanes */
	for (int i = 0; i < location.size(); i++)
	{
		/* creates the NORTH lane */
		if (location[i][size + 1] == NULL)
		{
			location[i][size + 1] = new Place;
			location[i][size + 1]->north = 1;
		}
		/* create the SOUTH lane */
		if (location[i][size] == NULL)
		{
			location[i][size] = new Place;
			location[i][size]->south = 1;
		}
	}
	/* EAST / WEST Bound lanes */
	for (int i = 0; i < location[0].size(); i++)
	{
		/* creates the WEST lane */
		if (location[size][i] == NULL)
		{
			location[size][i] = new Place;
			location[size][i]->west = 1;
		}
		else   // if the location is not null, this is an intersection
		{
			location[size][i]->intersection = 1;
			location[size][i]->north = 0;
			location[size][i]->south = 0;
			location[size][i]->east = 0;
			location[size][i]->west = 0;
		}
		/* creates the EAST lane */
		if (location[size + 1][i] == NULL)
		{
			location[size + 1][i] = new Place;
			location[size + 1][i]->east = 1;
		}
		else   // if the location is not null, this is an intersection
		{
			location[size + 1][i]->intersection = 1;
			location[size + 1][i]->north = 0;
			location[size + 1][i]->south = 0;
			location[size + 1][i]->east = 0;
			location[size + 1][i]->west = 0;
		}
	}

	/* initialize the start of all 4 lanes */
	north_start = location[location.size() - 1][size + 1];
	south_start = location[0][size];
	east_start = location[size + 1][0];
	west_start = location[size][location[0].size() - 1];

	/* store the intersection coordinates */
	for (int y = 0; y < location.size(); y++)
	{
		for (int x = 0; x < location[y].size(); x++)
		{
			if (location[y][x] != NULL && location[y][x]->intersection)
			{
				intersection_coords.push_back(location[y][x]);
			}
		}
	}

	int greenTimer = GREENLIGHT;

	northLight.setGreenTimer(greenTimer);
	southLight.setGreenTimer(greenTimer);
	eastLight.setGreenTimer(greenTimer);
	westLight.setGreenTimer(greenTimer);

	northLight.setRedTimer((greenTimer + YELLOWLIGHT) * 3);
	southLight.setRedTimer((greenTimer + YELLOWLIGHT) * 3);
	eastLight.setRedTimer((greenTimer + YELLOWLIGHT) * 3);
	westLight.setRedTimer((greenTimer + YELLOWLIGHT) * 3);

	northLight.setLight('R');
	southLight.setLight('R');
	eastLight.setLight('G');
	westLight.setLight('R');

	northLight.count = northLight.count - (greenTimer + YELLOWLIGHT) * 2;
	westLight.count = westLight.count - greenTimer - YELLOWLIGHT;
}

/* deconstructor */
Road::~Road()
{
	for (int y = 0; y < location.size(); y++)
	{
		for (int x = 0; x < location[y].size(); x++)
		{
			if (location[y][x] != NULL)
			{
				// delete the position at the coordinates and the location vector itself
				delete location[y][x]->position;
				delete location[y][x];
			}
		}
	}
}

/* queue() checks if a vehicle is waiting, and checks if the intersection is busy */
void Road::queue()
{
	if (!vehicle_queue.empty() && !isIntersectionBusy())
	{
		// temp is the vehicle first in queue
		Vehicle* temp = vehicle_queue.front();
		// pop the first vehicle waiting off queue
		vehicle_queue.pop_front();
		temp->isMoving = false;
		// moves the vehicle from the first place of vehicle
		move_Vehicle(temp->y1, temp->x1);
	}
}

/* move_Vehicle() moves vehicle along the road, checking for direction, intersection, and queue */
void Road::move_Vehicle(int y, int x)
{
	/* NORTH */
	if (location[y][x]->north)
	{
		// check if the the next spot has a position, and that the vehicle at this position hasnt already moved
		if (location[y - 1][x]->position == NULL && !location[y][x]->position->isMoving)
		{
			// if so then set the current location's vehicle to moving
			location[y][x]->position->isMoving = true;
			
			if (location[y - 1][x]->intersection && isIntersectionBusy()
				&& !inIntersection(location[y][x]->position))
			{
				if (!inQueue(location[y][x]->position))
				{
					vehicle_queue.push_back(location[y][x]->position);
				}
			}
			else
			{
				move_North(y, x);
			}
		}
	}
	/* SOUTH */
	else if (location[y][x]->south && !location[y][x]->position->isMoving)
	{
		// check if the the next spot has a position, and that the vehicle at this position hasnt already moved
		if (location[y + 1][x]->position == NULL)
		{
			// if so then set the current location's vehicle to moving
			location[y][x]->position->isMoving = true;

			if (location[y + 1][x]->intersection && isIntersectionBusy()
				&& !inIntersection(location[y][x]->position))
			{
				if (!inQueue(location[y][x]->position))
				{
					vehicle_queue.push_back(location[y][x]->position);
				}
			}
			else
			{
				move_South(y, x);
			}
		}
	}
	/* EAST */
	else if (location[y][x]->east && !location[y][x]->position->isMoving)
	{
		if (location[y][x + 1]->position == NULL)
		{
			location[y][x]->position->isMoving = true;
			if (location[y][x + 1]->intersection && isIntersectionBusy()
				&& !inIntersection(location[y][x]->position))
			{
				if (!inQueue(location[y][x]->position))
				{
					vehicle_queue.push_back(location[y][x]->position);
				}
			}
			else
			{
				move_East(y, x);
			}
		}
	}
	/* WEST */
	else if (location[y][x]->west && !location[y][x]->position->isMoving)
	{
		if (location[y][x - 1]->position == NULL)
		{
			location[y][x]->position->isMoving = true;

			if (location[y][x - 1]->intersection && isIntersectionBusy()
				&& !inIntersection(location[y][x]->position))
			{
				if (!inQueue(location[y][x]->position))
				{
					vehicle_queue.push_back(location[y][x]->position);
				}
			}
			else
			{
				move_West(y, x);
			}
		}
	}
	/* INTERSECTION */
	else if (location[y][x]->intersection)
	{
		if (location[y][x]->position != NULL && !location[y][x]->position->isMoving)
		{
			// figure out the direction we are heading
			/* NORTH */
			if (location[y][x]->position->direction == 'N')
			{
				location[y][x]->position->isMoving = true;

				// heading north but we want to turn west
				if (location[y][x]->position->destination == 'W')
				{
					location[y][x]->position->direction = 'W';
					move_North(y, x);		// move north so we can turn left
				}
				// heading north but we want to turn east
				else
				{
					if (location[y][x]->position->destination == 'E')
					{
						location[y][x]->position->direction == 'E';
					}
					move_East(y, x);
				}
			}
			/* SOUTH */
			else if (location[y][x]->position->direction = 'S')
			{
				location[y][x]->position->isMoving = true;

				// heading south but want to turn east
				if (location[y][x]->position->destination == 'E')
				{
					location[y][x]->position->direction = 'E';
					move_South(y, x);
				}
				// heading south but want to turn west
				else
				{
					if (location[y][x]->position->destination == 'W')
					{
						location[y][x]->position->direction = 'W';
					}
					move_West(y, x);
				}
			}
			/* EAST */
			else if (location[y][x]->position->direction = 'E')
			{
				location[y][x]->position->isMoving = true;

				// heading east but want to turn north
				if (location[y][x]->position->destination == 'N')
				{
					location[y][x]->position->direction = 'N';
					move_East(y, x); // move East once more so we can turn North
				}
				// heading east but want to turn south
				else
				{
					if (location[y][x]->position->destination == 'S')
					{
						location[y][x]->position->direction = 'S';
					}
					move_South(y, x);
				}
			}
			/* WEST */
			else if (location[y][x]->position->direction == 'W')
			{
				location[y][x]->position->isMoving = true;

				// heading west but want to turn north
				if (location[y][x]->position->destination == 'N')
				{
					location[y][x]->position->direction = 'N';
					move_North(y, x);
				}
				else
				{
					if (location[y][x]->position->destination == 'S')
					{
						location[y][x]->position->direction = 'S';
					}
					move_West(y, x);
				}
			}
		}
	}
}

/* all 4 directional movement methods */
void Road::move_North(int y, int x)
{
	location[y][x]->position->move_North(y, x);
}
void Road::move_South(int y, int x)
{
	location[y][x]->position->move_South(y, x);
}
void Road::move_East(int y, int x)
{
	location[y][x]->position->move_East(y, x);
}
void Road::move_West(int y, int x)
{
	location[y][x]->position->move_West(y, x);
}

/* isIntersectionBusy() checks if the intersection currently has a vehicle in it */
bool Road::isIntersectionBusy()
{
	bool busy = false;
	// loop through intersection coordinate vector to determine if a vehicle is at those coords
	for (int i = 0; i < intersection_coords.size(); i++)
	{
		if (intersection_coords[i]->position != NULL)
		{
			busy = true;
			break;
		}
	}
	return busy;
}

/* inQueue() takes a vehicle as an input and searches for it within the vehicle queue vector */
bool Road::inQueue(Vehicle const* v)
{
	return find(vehicle_queue.begin(), vehicle_queue.end(), v) != vehicle_queue.end();
}

/* inIntersection() takes a vehicle pointer and determines if THIS vehicle is in the intersection */
bool Road::inIntersection(Vehicle const* v)
{
	bool busy = false;
	for (int i = 0; i < intersection_coords.size(); i++)
	{
		if (intersection_coords[i]->position != NULL && intersection_coords[i]->position == v)
		{
			busy = true;
			break;
		}
	}
	return busy;
}

/* output() will place the lanes character and vehicle to the road */
void Road::output()
{
	cout << "\n";
	for (int y = 0; y < location.size(); y++)
	{
		for (int x = 0; x < location[y].size(); x++)
		{
			if (location[y][x] != NULL)
			{
				if (location[y][x]->position == NULL)
				{
					cout << print_lanes(*location[y][x]);
					SetConsoleTextAttribute(colorOutput, RESET);
				}
				else
				{
					cout << print_vehType(*location[y][x]->position);
					SetConsoleTextAttribute(colorOutput, RESET);
				}
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
}

/* place_Vehicle() places a vehicle object of different types onto the road in a direction */
void Road::place_Vehicle()
{
	int size = gridSize;
	int choice = rand() % 4;

	Vehicle* temp = NULL;
	/* determine vehicle type to be placed randomly */
	switch (choice)
	{
	case 0:
		temp = new Car(location);
		break;
	case 1:
		temp = new Motorcycle(location);
		break;
	case 2:
		temp = new Bus(location);
		break;
	case 3:
		temp = new Truck(location);
		break;
	}

	/* determine direction and begin the vehicle on its correct lane */
	switch (temp->getDirection())
	{
	case 'N':
		if (north_start->position == NULL)
		{
			temp->y1 = location.size() - 1;
			temp->x1 = size / 2 + 1;
			north_start->position = temp;
		}
		else
		{
			delete temp;
		}
		break;
	case 'S':
		if (south_start->position == NULL)
		{
			temp->y1 = 0;
			temp->x1 = size / 2;
			south_start->position = temp;
		}
		else
		{
			delete temp;
		}
		break;
	case 'E':
		if (east_start->position == NULL)
		{
			temp->y1 = size / 2 + 1;
			temp->x1 = 0;
			east_start->position = temp;
		}
		else
		{
			delete temp;
		}
		break;
	case 'W':
		if (west_start->position == NULL)
		{
			temp->y1 = size / 2;
			temp->x1 = location.size() - 1;
			west_start->position = temp;
		}
		else
		{
			delete temp;
		}
		break;

	default:
		break;
	}
}

/**/
void Road::update()
{
	/* begin cycle for all 4 directional traffic lights */
	northLight.light_cycle();
	southLight.light_cycle();
	eastLight.light_cycle();
	westLight.light_cycle();

	for (int i = 0; i < vehicle_queue.size(); i++)
	{
		vehicle_queue[i]->isMoving = true;
	}

	/* moves vehicles in the south and east lanes and deletes them when they are beyond our grid */
	for (int y = location.size() - 1; y != -1; y--)
	{
		for (int x = 0; x < location[y].size(); x++)
		{
			if (location[y][x] != NULL && location[y][x]->position != NULL)
			{
				if (location[y][x]->position->y1 == y && location[y][x]->position->x1 == x
					 && (location[y][x]->south || location[y][x]->east))
				{
					move_Vehicle(y, x);
				}

				// update queue
				queue();

				// determine if the vehicle reaches the end of the road and delete and set to NULL
				int size = gridSize;
				// NORTH
				delete location[0][size / 2 + 1]->position;
				location[0][size / 2 + 1]->position = NULL;
				// SOUTH
				delete location[location.size() - 1][size / 2]->position;
				location[location.size() - 1][size / 2]->position = NULL;
				// EAST 
				delete location[size / 2 + 1][location[0].size() - 1]->position;
				location[size / 2 + 1][location[0].size() - 1]->position = NULL;
				// WEST
				delete location[size / 2][0]->position;
				location[size / 2][0]->position = NULL;
			}
		}
	}
	/* move vehicles in north and west bound lanes and deletes them if they reach end of road */
	for (int y = 0; y < location.size(); y++)
	{
		for (int x = location[y].size() - 1; x != -1; x--)
		{
			if (location[y][x] != NULL && location[y][x]->position != NULL)
			{
				if (location[y][x]->position->y1 == y && location[y][x]->position->x1 == x)
				{
					move_Vehicle(y, x);
				}

				// update queue
				queue();

				/* determine if the vehicle reaches the end of the road and delete and set to NULL*/
				int size = gridSize;
				/* NORTH */
				delete location[0][size / 2 + 1]->position;
				location[0][size / 2 + 1]->position = NULL;
				/* SOUTH */
				delete location[location.size() - 1][size / 2]->position;
				location[location.size() - 1][size / 2]->position = NULL;
				/* EAST */
				delete location[size / 2 + 1][location[0].size() - 1]->position;
				location[size / 2 + 1][location[0].size() - 1]->position = NULL;
				/* WEST */
				delete location[size / 2][0]->position;
				location[size / 2][0]->position = NULL;
			}
		}
	}
	
	for (int y = 0; y < location.size(); y++)
	{
		for (int x = 0; x < location[y].size(); x++)
		{
			if (location[y][x] != NULL && location[y][x]->position != NULL)
			{
				location[y][x]->position->isMoving = false;
			}
		}
	}
}

/* print_lanes() places the appropriate character for the lane */
string Road::print_lanes(Place& p)
{
	if (p.intersection)
	{
		return "+";
	}
	else if (p.north)
	{
		return "N";
	}
	else if (p.south)
	{
		return "S";
	}
	else if (p.east)
	{
		return "E";
	}
	else if (p.west)
	{
		return "W";
	}
	else
	{
		return " ";
	}
}

/* print_vehType() places the appropriate vehicle and color scheme */
string Road::print_vehType(Vehicle& v)
{
	/* CAR */
	if (Car* temp = dynamic_cast<Car*>(&v))
	{
		string color = temp->getColor();

		if (color == "Navy")
		{
			SetConsoleTextAttribute(colorOutput, NAVY);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Green")
		{
			SetConsoleTextAttribute(colorOutput, GREEN);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Teal")
		{
			SetConsoleTextAttribute(colorOutput, TEAL);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Red")
		{
			SetConsoleTextAttribute(colorOutput, RED);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Purple")
		{
			SetConsoleTextAttribute(colorOutput, PURPLE);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Gold")
		{
			SetConsoleTextAttribute(colorOutput, GOLD);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Silver")
		{
			SetConsoleTextAttribute(colorOutput, SILVER);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Blue")
		{
			SetConsoleTextAttribute(colorOutput, BLUE);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Lime")
		{
			SetConsoleTextAttribute(colorOutput, LIME);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Cyan")
		{
			SetConsoleTextAttribute(colorOutput, TEAL);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (color == "Magenta")
		{
			SetConsoleTextAttribute(colorOutput, MAGENTA);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else
		{
			SetConsoleTextAttribute(colorOutput, 31);
			return "C";
			SetConsoleTextAttribute(colorOutput, RESET);
		}

	}
	/* BUS */
	else if (Bus* temp = dynamic_cast<Bus*>(&v))
	{
		string type = temp->getType();

		if (type == "MBTA")
		{
			SetConsoleTextAttribute(colorOutput, 192);
			return "B";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else if (type == "School")
		{
			SetConsoleTextAttribute(colorOutput, 96);
			return "B";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
		else
		{
			SetConsoleTextAttribute(colorOutput, 96);
			return "B";
			SetConsoleTextAttribute(colorOutput, RESET);
		}
	}
	/* MOTORCYCLE */
	else if (Motorcycle* temp = dynamic_cast<Motorcycle*>(&v))
	{
		SetConsoleTextAttribute(colorOutput, 47);
		return "M";
		SetConsoleTextAttribute(colorOutput, RESET);
	}
	/* TRUCK */
	else if (Truck* temp = dynamic_cast<Truck*>(&v))
	{
		SetConsoleTextAttribute(colorOutput, 95);
		return "T";
		SetConsoleTextAttribute(colorOutput, RESET);
	}
}

/* output operator overload */
ostream& operator<<(ostream& os, Road& r)
{
	SetConsoleTextAttribute(colorOutput, RESET);
	cout << "\nNorth Light: " << r.northLight;
	cout << "\nSouth Light: " << r.southLight;
	cout << "\nEast Light: " << r.eastLight;
	cout << "\nWest Light: " << r.westLight;

	r.output();
	return os;
}