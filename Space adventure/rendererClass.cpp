#include "rendererClass.h"

// Push gameobject into render queue
void rendererClass::pushIntoRenderQueue(gameObject* object) {
		renderQueue.push_back(object);
}

// Renderloop - draws everything in renderqueue
void rendererClass::drawRenderQueue() {

	// Iterators
	std::vector<gameObject*>::iterator it;
	std::vector<gameObject*>::iterator collIt;

	for(it = renderQueue.begin(); it != renderQueue.end();) {
		// Object collisions
		for (collIt = renderQueue.begin(); collIt != renderQueue.end(); collIt++) {
			// If objects collide and both have collisionEnabled set to true			
			if( ((*it)->checkCollision(*collIt)) && ((*it)->collisionEnabled && (*collIt)->collisionEnabled)) {
				if (*it != *collIt) {
					// Do collision events for both object
					(*it)->collisionEvent();
					(*collIt)->collisionEvent();
				}
			}
		}

		// Update position for all objects
		(*it)->updatePosition();

		// Draw all objects
		(*it)->drawObject();

	// Delete objects that are flagged for deletion
		if ((*it)->deleteThis == true) {
			delete *it;
			it = renderQueue.erase(it);
		}
		else
			it++;
	}
}
