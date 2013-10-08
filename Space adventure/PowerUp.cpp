#include "PowerUp.h"


PowerUp::PowerUp(pUpType ptype)
{
	pupType = ptype;

	if (y < 0 || y > 480) {
		std::random_device rng;
		y = rng() % 460 + 10;

	}

	x = 690;
	maxSpeed = 5;

	customCollision = false;
	collisionBuffer = 0;
	collisionEnabled = true;
	collisionDetected = false;
	objectType = "powerup";

	objectTexture = nullptr;

	switch (pupType) {
		case HEALTH:
			objectTexture = LoadImage("data\\puphealth.png");
			pointWorth = 500;
			break;
		case TRIAMMO:
			objectTexture = LoadImage("data\\pupthree.png");
			pointWorth = 100;
			break;
		case MULTIFIRE:
			objectTexture = LoadImage("data\\pupmulti.png");
			pointWorth = 250;
			break;
		default:
			break;
	}
}

int PowerUp::collisionEvent() {

	collisionDetected = true;

	return 0;
}

int PowerUp::updatePosition() {

	x -= 4;

	if (collisionDetected) {
		deleteThis = true;
	}

	return 0;
}


PowerUp::~PowerUp(void)
{
}
