#include "LevelEvent.h"


LevelEvent::LevelEvent(int eY, Uint32 eTi, std::string eTy)
{
	// Set event information
	eventY = eY;
	eventTime = eTi;

	// NOTE - DIRTY HACK TO REMOVE THE DELIMITER
	eventType = eTy.substr(0, eTy.size()-1);;

}


LevelEvent::~LevelEvent(void)
{
}

gameObject* LevelEvent::fireEvent() {
	
	gameObject* returnedObject = nullptr;

	if (eventType == "DORP") {
		returnedObject = new Enemy(Enemy::DORP);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}
	else if (eventType == "MORP") {
		returnedObject = new Enemy(Enemy::MORP);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}

	else if (eventType == "BENE") {
		returnedObject = new Enemy(Enemy::BENE);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}

	else if (eventType == "MONSTRO") {
		returnedObject = new Enemy(Enemy::MONSTRO);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}
	else if (eventType == "EBULLET") {
		returnedObject = new bulletClass(520, eventY, -1);
		if (eventY == 200) {
			returnedObject->setTarget(1);
		}
		else if (eventY == 220) {
			returnedObject->setTarget(479);
		}

		return returnedObject;
	}
	else if (eventType == "HEALTH") {
		returnedObject = new PowerUp(PowerUp::HEALTH);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}
	else if (eventType == "TRIAMMO") {
		returnedObject = new PowerUp(PowerUp::TRIAMMO);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}
	else if (eventType == "MULTIFIRE") {
		returnedObject = new PowerUp(PowerUp::MULTIFIRE);
		returnedObject->x = 680;
		returnedObject->y = eventY;

		return returnedObject;
	}
	else
		return nullptr;

}