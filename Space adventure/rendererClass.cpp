#include "rendererClass.h"

rendererClass::rendererClass() { 
	scroreToBeAdded = 0;
}

// Push gameobject into render queue
void rendererClass::pushIntoRenderQueue(gameObject* object) {
		renderQueue.push_back(object);
}

// Renderloop - draws everything in renderqueue
void rendererClass::drawRenderQueue() {

	// Iterators
	std::vector<gameObject*>::iterator it;

	for(it = renderQueue.begin(); it != renderQueue.end();it++) {
		// Draw all objects
		(*it)->drawObject();
	}
}

void rendererClass::handleLogicQueue() {
	// Iterators
	std::vector<gameObject*>::iterator it;
	std::vector<gameObject*>::iterator collIt;


	for(it = renderQueue.begin(); it != renderQueue.end();) {
		// Object collisions
		for (collIt = renderQueue.begin(); collIt != renderQueue.end(); collIt++) {
			// objects of same objectType colliding will be ignored
			if ((*it)->objectType != (*collIt)->objectType) {
				// If objects collide and both have collisionEnabled set to true
				if( ((*it)->checkCollision(*collIt)) && ((*it)->collisionEnabled && (*collIt)->collisionEnabled)) {
					if (*it != *collIt) {

						// Add scores if bullet and enemy collide
						if ((*it)->objectType == "bullet" && (*collIt)->objectType == "enemy") {
							scroreToBeAdded += (*collIt)->pointWorth;
						}
						else if ((*it)->objectType == "enemy" && (*collIt)->objectType == "bullet") {
							scroreToBeAdded += (*it)->pointWorth;
						}

						// Do collision events for both object
						(*it)->collisionEvent();
						(*collIt)->collisionEvent();
					}
				}
			}
		}
	
	// Add scores to player score, and reset the counter
	if ((*it)->objectType == "player" && scroreToBeAdded != 0) {
		(*it)->addScore(scroreToBeAdded);
		scroreToBeAdded = 0;
	}

	// Update position for all objects
	(*it)->updatePosition();

	// Delete objects that are flagged for deletion
		if ((*it)->deleteThis == true) {
			delete *it;
			it = renderQueue.erase(it);
		} else {
			it++;
		}
		
	}
}