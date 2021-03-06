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

	// Tracks frames
	int currentFrame;
	int totalFrames;
	int framesPlayed;

	// Control the speed of animation
	Uint32 animationTime;
	int animationRate;

	// Animation constructor, load texture, frames, rows in sprite file, animationrate
	// Default animationRate = 12
	Animation(std::string filePath, int frames, int frameRows = 0, int animRate = 12);
	~Animation(void);
	
	// Enum for direction of scrollAnimation
	enum scrollDirection { UP, DOWN, LEFT, RIGHT };

	// scrollAnimation for backgrounds
	bool scrollAnimation(scrollDirection scrollDir);

	// Plays animation
	bool playAnimation();
	bool playAnimationOnce();

	// Check if animation playing, returns TRUE if yes
	bool animationPlaying();
	
};

#endif