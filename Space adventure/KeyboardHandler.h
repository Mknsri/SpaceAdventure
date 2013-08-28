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

	// If user leaves game
	bool quitPressed;
	
	KeyboardHandler(void);
	~KeyboardHandler(void);

	// Handle keyboard events for play
	void handleKeyboardEvents(playerClass& playerObj, rendererClass &renderer);
	
	// Checks if single key is pressed
	bool isPressed(int keyCode);
};

#endif