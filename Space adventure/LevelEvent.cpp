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

}