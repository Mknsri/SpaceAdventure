#ifndef MOTION_H
#define MOTION_H

#include "SDL.h"

class Motion
{
public:

	// size of each step
	int stepSize;

	// Current step of motion
	int motionFrame;

	// The update position of object
	int newPosition;

	// Motion time
	Uint32 motionTime;

	Motion(void);
	~Motion(void);

	// Wave motion, takes starting point, range of pixels and duration in frames
	int waveMotion(int startingPosition, int waveRange, int waveDuration);

};

#endif