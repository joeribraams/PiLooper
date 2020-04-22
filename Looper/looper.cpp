#include "looper.h"
#include <iostream>
#include <wiringPi.h>

using namespace std;

Looper::Looper()
{
	wiringPiSetup();
	pinMode(0, INPUT);
	pinMode(1, OUTPUT);

	buffer.push_back(0);
}

Looper::~Looper()
{

}



float Looper::sample(float input)
{
	if(digitalRead(0) == 1)
	{
		recording = true;
		holdTime++;
		if(playing == false)
		{
			buffer.push_back(input);
		}
		else
		{
			buffer[step] = buffer.at(step) + input;
		}
	}
	if(recording == true && digitalRead(0) == 0)
	{
		recording = false;
		playing = true;
		if(holdTime < 10000 && holdTime > 10)
		{
			playing = false;
			buffer.clear();
			buffer.push_back(0);
			step = 0;
		}
		cout << holdTime << endl;
		holdTime = 0;
	}

	if(step < buffer.size()-1)
	{
		step++;
	}
	else
	{
		step = 0;
	}

	if(playing == true)
	{
		output = buffer.at(step);
	}
	else
	{
		output = 0;
	}

	digitalWrite(1, playing);

	return input + output;
}
