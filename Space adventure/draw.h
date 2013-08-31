#ifndef DRAW_H
#define DRAW_H  

#include "SDL_image.h"
#include "SDL.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

//Screen attributes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

// Starts SDL
int initSDL();

// Load texture from image
SDL_Texture* LoadImage(std::string file);


// Draw texture on surface
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Rect* clip = nullptr);

// Update screen
void updateScreen();

// Clear screen
void clearScreen();

// This function takes SDL_Surface and returns it as SDL_Texture
SDL_Texture* surfaceIntoTexture(SDL_Surface* surface);

#endif 









