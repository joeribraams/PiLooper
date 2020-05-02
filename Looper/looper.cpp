#include "looper.h"
#include <iostream>
#include <wiringPi.h>

using namespace std;

// Constructor and destructor
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


// Process 1 sample
float Looper::sample(float input)
{
	if(digitalRead(0) == 1) // If switch is pressed
	{
		recording = true;
		holdTime++;

		if(!playing) // If we're recording a new loop
		{
			buffer.push_back(input);
		}
		else // If we're overdubbing on an existing loop
		{
			buffer[step] = buffer.at(step) + input;
		}
	}

	if(recording && digitalRead(0) == 0) // When switch is released
	{
		recording = false;
		playing = true;

		if(holdTime < 5000 && holdTime > 50) // If switch was only tapped, stop loop
		{
			playing = false;
			buffer.clear();
			buffer.push_back(0);
			step = 0;
		}

		holdTime = 0;
	}

	if(step++ >= buffer.size() - 1) // Wrap step value
	{
		step = 0;
	}

	digitalWrite(1, playing); // Light led

	if(playing == true) // Output dry signal or dry and loop
	{
		return input + buffer.at(step);
	}
	else
	{
		return input;
	}
}
