#ifndef EVENTS_H
#define EVENTS_H

#include "player.h"
#include "rendererClass.h"
#include "file.h"

#include "SDL.h"

int handleEvents();
int handleKeyboardEvents(playerClass* playerObj, rendererClass &renderer);

#endif
