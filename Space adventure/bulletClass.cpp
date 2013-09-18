#include "bulletClass.h"


bulletClass::bulletClass(int startX, int startY) {
	
	objectTexture = LoadImage("data\\bullet.png");
	
	objectType = "bullet";

	// Set deletion flag
	deleteThis = false;

	// Offset starting position
	x = startX + 75;
	y = startY + 30;

	// Collision buffer 2px
	collisionBuffer = 2;

	// Enable collision
	collisionEnabled = true;
	collisionDetected = false;
	
}

int bulletClass::updatePosition() {

	
	x += 10;

	if (x > 640)
		deleteThis = true;


	return 0;
}

bulletClass::~bulletClass() {
	
}

int bulletClass::collisionEvent() {
	
	deleteThis = true;

	return 0;
}