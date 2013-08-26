#include "player.h"

playerClass::playerClass() {
	try { 
		objectTexture = LoadImage("C:\\Users\\make\\Documents\\kalalus.png");
	}
	catch (const std::runtime_error &e){
        errorToFile(e.what());
	}

	collisionBuffer = 5;
	x = 10;
	y = 10;
	xVelocity = 0;
	yVelocity = 0;
	deleteThis = false;
	maxSpeed = 5;
	collisionEnabled = true;
}

void playerClass::playerFire() {
};

int playerClass::updatePosition() {
	
	if (x > 585 )
		x = 585;
	if (x < 5)
		x = 5;
	
	x += xVelocity * maxSpeed;

	if (y > 425 )
		y = 425;
	if (y < 5)
		y = 5;
	
		y += yVelocity * maxSpeed;

	return 0;
}

int playerClass::collisionEvent()  {
	return 0;
}