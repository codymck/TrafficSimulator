// Traffic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>

#include "Road.h"
#include "TrafficLight.h"

#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"
#include "Truck.h"

HANDLE colorO = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    int gLight = 8;
    srand(time(NULL));
    // create the directional lights
    TrafficLight North, South, East, West;

    // create the timers
    North.setGreenTimer(gLight);
    South.setGreenTimer(gLight);
    East.setGreenTimer(gLight);
    West.setGreenTimer(gLight);

    North.setRedTimer((gLight + YELLOWLIGHT) * 2);
    South.setRedTimer((gLight + YELLOWLIGHT) * 2);
    East.setRedTimer((gLight + YELLOWLIGHT) * 2);
    West.setRedTimer((gLight + YELLOWLIGHT) * 2);

    North.setLight('R');
    South.setLight('R');
    East.setLight('E');
    West.setLight('R');

    // create the count
    North.count = North.count - (gLight - YELLOWLIGHT) * 2;
    South.count = South.count - (gLight - YELLOWLIGHT) * 2;
    West.count = West.count - gLight - YELLOWLIGHT;

    Road lanes;
    for (int i = 0; i < 4; i++)
    {
        lanes.place_Vehicle();
        cout << lanes;
        lanes.update();
        cout << lanes;
        lanes.place_Vehicle();
        SetConsoleTextAttribute(colorO, RESET);
    }

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0 && i < 50)
        {
            lanes.place_Vehicle();
            SetConsoleTextAttribute(colorO, RESET);
        }
        lanes.update();
        cout << lanes;
        SetConsoleTextAttribute(colorO, RESET);
    }
}