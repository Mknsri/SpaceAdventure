#include "rendererClass.h"

void rendererClass::pushIntoRenderQueue(gameObject* object) {
		renderQueue.push_back(object);
}

void rendererClass::drawRenderQueue() {
	// Renderloop
	std::vector<gameObject*>::iterator it;
	std::vector<gameObject*>::iterator collIt;
	for(it = renderQueue.begin(); it != renderQueue.end();) {
		// Object collisions
		for (collIt = renderQueue.begin(); collIt != renderQueue.end(); collIt++) {
			// If objects collide and both have collisionEnabled set to true			
			if( ((*it)->checkCollision(*collIt)) && ((*it)->collisionEnabled && (*collIt)->collisionEnabled)) {
				if (*it != *collIt) {
					(*it)->collisionEvent();
					(*collIt)->collisionEvent();
				}
			}
		}
		(*it)->updatePosition();
		(*it)->drawObject();
	// Delete object if out of bounds
		if ((*it)->deleteThis == true) {
			delete *it;
			it = renderQueue.erase(it);
		}
		else
			it++;
	}
}
