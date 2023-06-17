#include "TrafficLight.h"

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

/* TrafficLight constructor */
TrafficLight::TrafficLight()
{
	*this = TrafficLight::TrafficLight(GREENLIGHT, GREENLIGHT + YELLOWLIGHT);
}

/* TrafficLight constructor takes an int for green and red light */
TrafficLight::TrafficLight(int g, int r)
{
	currLight = 'G';
	this->greenTimer = g;
	this->yellowTimer = YELLOWLIGHT;
	this->redTimer = r;
	count = greenTimer;
}

/* light_cycle decrements our light count and switches the light when the timer is zero  */
void TrafficLight::light_cycle()
{
	if (--count == 0)
	{
		lightSwitch();
	}
}

/* light switch determines the current light status and changes it to the appropriate next light */
void TrafficLight::lightSwitch()
{
	switch (currLight)
	{
	case 'G':
		setLight('Y');
		break;
	case 'Y':
		setLight('R');
		break;
	case 'R':
		setLight('G');
		break;
	default:
		break;
	}
}

// return current light
char TrafficLight::checkLight()
{
	return currLight;
}

// light setters
void TrafficLight::setGreenTimer(int t)
{
	greenTimer = t;
}

void TrafficLight::setRedTimer(int t)
{
	redTimer = t;
}

void TrafficLight::setLight(char light)
{
	currLight = light;
	switch (currLight)
	{
	case 'G':
		count = greenTimer;
		break;
	case 'Y':
		count = yellowTimer;
		break;
	case 'R':
		count = redTimer;
		break;
	default:
		break;
	}
}

// return green and red timer
int TrafficLight::getGreenTimer()
{
	return greenTimer;
}
int TrafficLight::getRedTimer()
{
	return redTimer;
}

// operator overload output to output the color of the traffic light
ostream &operator<<(ostream &os, TrafficLight &t)
{
	if (t.checkLight() == 'G')
	{
		SetConsoleTextAttribute(color, GREEN);
		cout << "Green ";
		SetConsoleTextAttribute(color, RESET);
	}
	else if (t.checkLight() == 'Y')
	{
		SetConsoleTextAttribute(color, YELLOW);
		cout << "Yellow ";
		SetConsoleTextAttribute(color, RESET);
	}
	else
	{
		SetConsoleTextAttribute(color, RED);
		cout << "Red ";
		SetConsoleTextAttribute(color, RESET);
	}
	cout << t.count << " seconds";
	return os;
}
