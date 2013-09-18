#include "Motion.h"


Motion::Motion(void)
{

	// Define members
	motionTime = SDL_GetTicks();
	motionFrame = 0;

	// The new position to return
	newPosition = 1;

}


Motion::~Motion(void)
{
}


int Motion::waveMotion(int startingPosition, int waveRange, int waveDuration) {

	newPosition = startingPosition;

	if (motionFrame == 0 || motionFrame == waveDuration * 0.25 || motionFrame == waveDuration * 0.5 || motionFrame == waveDuration * 0.75) {
		stepSize = 1;
	}
	else
	{
		stepSize++;
	}

	// After half the frames have passed, switch direction
	if (motionFrame < waveDuration / 2) {
		// Check that we dont go out of range
		newPosition += stepSize;
	}
	// Reverse direction
	else if (motionFrame > waveDuration / 2 && motionFrame != waveDuration) {
		// Check that we dont go out of range
		newPosition -= stepSize;

	}

	// Add frame to counter or reset if we've shown all the frames
	if (motionFrame == waveDuration) {
		motionFrame = 0;
	}
	else {
		motionFrame++;
	}

	return newPosition;

}
