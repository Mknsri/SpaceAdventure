#include "bulletClass.h"


bulletClass::bulletClass(int startX, int startY) {
	
	try {
	objectTexture = LoadImage("data\\bullet.png");
	}
	catch (const std::runtime_error &e){
        errorToFile(e.what());
	}
	
	explosionAnim = new Animation("data\\explosionanim.png",5,0,6);

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

	
	x += 5;

	if (x > 640)
		deleteThis = true;

	if (explosionAnim->animationPlaying() && collisionDetected == true) {
		objectTexture = nullptr;
		explosionAnim->playAnimationOnce();
	}
	else if ( explosionAnim->animationPlaying() == false && collisionDetected == true)
		deleteThis = true;

	return 0;
}

bulletClass::~bulletClass() {
	
}

int bulletClass::collisionEvent() {

	explosionAnim->x = x - 50;
	explosionAnim->y = y - 50;
	collisionDetected = true;

	return 0;
}