#ifndef RENDERER_H 
#define RENDERER_H

#include "draw.h"
#include "gameObject.h"
#include "Animation.h"

class rendererClass
{
public:
	// Render queue vector
	std::vector<gameObject*> renderQueue;

	// Queue for game logic
	std::vector<gameObject*> logicQueue;


	// Push object into render queue
	void pushIntoRenderQueue(gameObject* object);

	// Draw everything in the render queue
	void drawRenderQueue();

	// Handle events in the logic queue
	void handleLogicQueue();
};

#endif
