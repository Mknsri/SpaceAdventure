#ifndef RENDERER_H 
#define RENDERER_H

#include "file.h"
#include "draw.h"
#include "gameObject.h"

class rendererClass
{
public:
	// Render queue vector
	std::vector<gameObject*> renderQueue;

	// Push object into render queue
	void pushIntoRenderQueue(gameObject* object);

	// Draw everything in the render queue
	void drawRenderQueue();

};

#endif
