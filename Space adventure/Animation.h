#ifndef ANIMATION_H
#define ANIMATION_H

#include "draw.h"

#include "SDL.h"

#include <string>


class Animation
{
public:

	SDL_Texture* animationTexture;
	SDL_Rect* animationClips;

	int x, y;
	int currentFrame;
	int totalFrames;

	// Control the speed of animation
	Uint32 animationStartTime;
	int animationRate;


	int frameSizeW, frameSizeH;

	Animation(std::string filePath, int frames, int frameRows = 0, int animRate = 12);
	~Animation(void);
	
	bool playAnimation();
	
};

#endif