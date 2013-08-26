#ifndef DRAW_H
#define DRAW_H  

#include "SDL_image.h"
#include "SDL.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int initSDL();

SDL_Texture* LoadImage(std::string file);

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Rect* clip = nullptr);

void updateScreen();

void clearScreen();

SDL_Texture* surfaceIntoTexture(SDL_Surface* surface);

#endif 









