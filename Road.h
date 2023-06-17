#pragma once
#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include <queue>
#include <memory>
#include <iostream>
#include <set>

#include "Place.h"
#include "Car.h"
#include "Bus.h"
#include "Motorcycle.h"
#include "Truck.h"
#include "TrafficLight.h"

#define gridSize 42

/* color codes */
#define NAVY 1
#define GREEN 2.
#define TEAL 3
#define RED 4
#define PURPLE 5
#define GOLD 6
#define SILVER 8
#define BLUE 9
#define LIME 10
#define TEAL 11
#define MAGENTA 13
#define RESET 7		// puts back to white

class Road
{
public:
	Road();
	~Road();

	vector<vector<Place*>> location;

	/* print the lanes and intersection */
	void output();
	/* place random vehicles on a lane */
	void place_Vehicle();
	/* update vehicle movement */
	void update();

private:
	/* direction starts */
	Place* north_start;
	Place* south_start;
	Place* east_start;
	Place* west_start;

	/* queue for moving vehicles */
	void queue();
	/* method to move vehicles */
	void move_Vehicle(int y, int x);

	/* check if intersection is full */
	bool isIntersectionBusy(); // checkInter
	/* check if a vehicle is waiting */
	bool inQueue(Vehicle const* v);
	/* if current vehicle is in an intersection */
	bool inIntersection(Vehicle const* v); // already in inter

	/* directional movement methods */
	void move_North(int y, int x);
	void move_South(int y, int x);
	void move_East(int y, int x);
	void move_West(int y, int x);

	/* print_lanes will place the appropriate character per lane */
	string print_lanes(Place& p);
	/* print_vehType will coordinate color and character for a vehicle */
	string print_vehType(Vehicle& v);

	/* double ended queue for vehicle queue */
	deque<Vehicle*> vehicle_queue;
	/* vector of Place* to save coordinates of intersections */
	vector<Place*> intersection_coords;
	TrafficLight northLight, westLight, eastLight, southLight;
	friend ostream& operator<<(ostream& os, Road& r);
};
#endif