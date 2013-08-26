#include "bulletClass.h"


bulletClass::bulletClass(int startX, int startY) {
	
	try {
	objectTexture = LoadImage("C:\\Users\\make\\Documents\\bullet.png");
	}
	catch (const std::runtime_error &e){
        errorToFile(e.what());
	}
	
	deleteThis = false;
	x = startX + 75;
	y = startY + 30;
	collisionBuffer = 2;
	collisionEnabled = true;
	
}

int bulletClass::updatePosition() {
	x += 5;
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