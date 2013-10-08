#include "bulletClass.h"


bulletClass::bulletClass(int startX, int startY, int bullDir) {
	
	// Set maxspeed to default
	maxSpeed = 10;

	// Determine if shot by enemy or player
	// by checking bullet direction
	if (bullDir == 1) {
		objectTexture = LoadImage("data\\bullet.png");
	}
	else {
		maxSpeed = 8;
		objectTexture = LoadImage("data\\ebullet.png");
	}

	objectType = "bullet";

	// Set deletion flag
	deleteThis = false;

	// Offset starting position
	x = startX;
	y = startY;

	// Bullet direction modifier, 1 = Right, -1 = left
	bulletDirectionModifier = bullDir;

	// Collision buffer 2px
	collisionBuffer = 2;

	// Enable collision
	collisionEnabled = true;
	collisionDetected = false;
	
	bulletTargetY = -1;

}

int bulletClass::updatePosition() {

	// Bullet travels towards target height
	if (bulletTargetY != -1) {
		if (y < bulletTargetY) {
			y += 3;
		}
		else if (y > bulletTargetY) {
			y -= 3;
		}

	}

	x += bulletDirectionModifier * maxSpeed;
	
	if (x > 700 || x < 0) {
		deleteThis = true;
	}


	return 0;
}

bulletClass::~bulletClass() {
	
}

int bulletClass::collisionEvent() {
	
	deleteThis = true;

	return 0;
}

void bulletClass::setTarget(int targetY) {
	bulletTargetY = targetY;
}