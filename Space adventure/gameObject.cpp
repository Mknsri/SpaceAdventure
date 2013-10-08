#include "gameObject.h"

gameObject::gameObject(void) { deleteThis = false; health = 1; customCollision = false; }


gameObject::~gameObject(void) {}

int gameObject::updatePosition() { return 0; }

int gameObject::drawObject() {
	ApplySurface(x,y,objectTexture);
	return 0;
}


bool gameObject::checkCollision(gameObject * collObject) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate object 1
	collisionBox.x = x;
	collisionBox.y = y;

	if (objectTexture != nullptr && !customCollision) {
		SDL_QueryTexture(objectTexture, NULL, NULL, &collisionBox.w, &collisionBox.h);
	}
	else if (collBoxH > 0 && collBoxW > 0)
	{
		collisionBox.h = collBoxH;
		collisionBox.w = collBoxW;
	}

	// buffer collisionbox
	collisionBox.w -= collisionBuffer;
	collisionBox.h -= collisionBuffer;

	leftA = collisionBox.x;
	rightA = collisionBox.x + collisionBox.w;
	topA = collisionBox.y;
	bottomA = collisionBox.y + collisionBox.h;

	// Calculate object 2
	collObject->collisionBox.x = collObject->x;
	collObject->collisionBox.y = collObject->y;
	SDL_QueryTexture(collObject->objectTexture, NULL, NULL, &collObject->collisionBox.w, &collObject->collisionBox.h);
	
	leftB = collObject->collisionBox.x;
	rightB = collObject->collisionBox.x + collObject->collisionBox.w;
	topB = collObject->collisionBox.y;
	bottomB = collObject->collisionBox.y + collObject->collisionBox.h;

	 //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
} 

int gameObject::collisionEvent() {
	return 0;
}

// Virtual functions
void gameObject::addScore(int points) {}
void gameObject::getObject(gameObject* obj) {}
void gameObject::setTarget(int targetY) {}
void gameObject::setPowerUp(powerUps powerup) {}
bool gameObject::checkPowerUp(powerUps powerup) { return false; }