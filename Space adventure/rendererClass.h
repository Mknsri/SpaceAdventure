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

	void pushIntoRenderQueue(gameObject* object);
	void drawRenderQueue();

};

#endif
