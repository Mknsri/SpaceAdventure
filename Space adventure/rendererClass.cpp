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
							(*collIt)->getObject((*it));
						}
						else if ((*it)->objectType == "enemy" && (*collIt)->objectType == "bullet") {
							scroreToBeAdded += (*it)->pointWorth;
							(*it)->getObject((*collIt));
						}
						
						// Check for powerup collisions
						if ((*it)->objectType == "player" && (*collIt)->objectType == "powerup") {
							// Add health
							if ((*collIt)->pointWorth == 500) {
								(*it)->health++;
							}
							else if ((*collIt)->pointWorth == 100) {
								(*it)->setPowerUp(gameObject::POWERUP_TRIAMMO);
							}
							else if ((*collIt)->pointWorth == 250) {
  								(*it)->setPowerUp(gameObject::POWERUP_MULTIFIRE);
							}
							(*collIt)->collisionEvent();
						}
						else if ((*it)->objectType == "powerup" && (*collIt)->objectType == "player") {
							// Add health
							if ((*it)->pointWorth == 500) {
								(*collIt)->health++;
							}
							else if ((*it)->pointWorth == 100) {
								(*collIt)->setPowerUp(gameObject::POWERUP_TRIAMMO);
							}
							else if ((*it)->pointWorth == 250) {
  								(*collIt)->setPowerUp(gameObject::POWERUP_MULTIFIRE);
							}
							(*it)->collisionEvent();
						}
						// Disable powerup and bullet/enemy collisions
						else if (((*it)->objectType == "bullet" && (*collIt)->objectType == "powerup") || 
								((*it)->objectType == "powerup" && (*collIt)->objectType == "bullet") || 
								((*it)->objectType == "powerup" && (*collIt)->objectType == "enemy") || 
								((*it)->objectType == "enemy" && (*collIt)->objectType == "powerup")) {}
						else {
							// Do collision events for both object
							(*it)->collisionEvent();
							(*collIt)->collisionEvent();
						}
					}
				}
			}	
			// Give player object data to enemy if needed
			if ((*it)->objectType == "enemy" && (*collIt)->objectType == "player") {
				if ((*it)->pointWorth > 20) {
					(*it)->getObject(*collIt);
				}
			}
			else if ((*it)->objectType == "player" && (*collIt)->objectType == "enemy") {
				if ((*collIt)->pointWorth > 20) {
					(*collIt)->getObject(*it);
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