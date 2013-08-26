#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include "player.h"
#include "rendererClass.h"
#include "bulletClass.h"
#include "file.h"
#include "Enemy.h"

#include "SDL.h"

#include <string>

class KeyboardHandler
{
public:
	bool quitPressed;
	
	KeyboardHandler(void);
	~KeyboardHandler(void);

	void handleKeyboardEvents(playerClass& playerObj, rendererClass &renderer);
	bool isPressed(int keyCode);
};

#endif