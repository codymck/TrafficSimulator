#pragma once
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <iostream>
#include <windows.h>

using namespace std;

#define YELLOWLIGHT 6
#define GREENLIGHT 12

#define RED 4
#define GREEN 2
#define YELLOW 6
#define RESET 7


class TrafficLight
{
private:
	int greenTimer;
	int redTimer;
	int yellowTimer;

	char currLight;

	void lightSwitch();
public:
	int count;

	TrafficLight();
	TrafficLight(int greenTime, int redTime);

	void light_cycle();

	char checkLight();

	void setGreenTimer(int t);
	void setRedTimer(int t);
	void setLight(char light);

	int getGreenTimer();
	int getRedTimer();
};
ostream& operator<<(ostream& os, TrafficLight& t);
#endif