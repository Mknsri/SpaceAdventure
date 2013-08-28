#include "player.h"

playerClass::playerClass() {

	// Load the texture for player
	try { 
		objectTexture = LoadImage("data\\kalalus.png");
	}
	catch (const std::runtime_error &e){
        errorToFile(e.what());
	}

	// Collisionbuffer, the pixel amount the collisionbox 
	// is feathered from the actual texture size
	collisionBuffer = 5;

	// Init position
	x = 10;
	y = 10;

	// Init speed
	xVelocity = 0;
	yVelocity = 0;

	// Set object not to be deleted
	deleteThis = false;

	// Max speed
	maxSpeed = 5;
	
	// Enable collision
	collisionEnabled = true;
}

void playerClass::playerFire() {
};

int playerClass::updatePosition() {
	
	// Out of bounds check
	if (x > SCREEN_WIDTH )
		x = SCREEN_WIDTH - 20;
	if (x < 10)
		x = 10;
	
	// Set speed
	x += xVelocity * maxSpeed;

	// Out of bounds check
	if (y > SCREEN_HEIGHT )
		y = SCREEN_HEIGHT - 20;
	if (y < 10)
		y = 10;
	
	// Set speed
		y += yVelocity * maxSpeed;

	return 0;
}

// Collision event
int playerClass::collisionEvent()  {
	return 0;
}