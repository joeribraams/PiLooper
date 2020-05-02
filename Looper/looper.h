#pragma once

#include <vector>

class Looper {
public:
	// For storing the samples
	std::vector<float> buffer;

	// Constructor and destructor
	Looper();
	~Looper();

	// Process 1 sample
	float sample(float input);

private:
	// Sample values
	float input = 0;
	float output = 0;

	// Place in loop
	unsigned int step = 0;

	// Stores state of system
	bool recording = false;
	bool playing = false;

	// For switch debounce
	unsigned int holdTime = 0;
};
