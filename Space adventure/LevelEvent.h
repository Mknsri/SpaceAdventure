#ifndef LEVEL_EVENT_H
#define LEVEL_EVENT_H

#include "PowerUp.h"
#include "bulletClass.h"
#include "player.h"
#include "gameObject.h"
#include "Enemy.h"

#include "SDL.h"

#include <string>

class LevelEvent
{
public:
	// Event starting point
	int eventY, eventX;

	// Event trigger time
	Uint32 eventTime;

	// Event type
	std::string eventType;
	
	// Set y-pos, time, type
	LevelEvent(int eY, Uint32 eTi, std::string eTy);
	~LevelEvent(void);

	// Function to trigger event
	gameObject* fireEvent();
};

#endif