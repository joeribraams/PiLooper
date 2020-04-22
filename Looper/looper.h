#pragma once

#include <vector>

class Looper {
public:
	std::vector<float> buffer;

	Looper();
	~Looper();

	float sample(float input);

private:
	float input = 0;
	float output = 0;
	unsigned int step = 0;

	bool recording = false;
	bool playing = false;
	unsigned int holdTime = 0;
};
