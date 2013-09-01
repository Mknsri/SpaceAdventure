#include "Animation.h"


Animation::Animation(std::string filePath, int frames, int frameRows, int animRate)
{

	// Load animation texture
	animationTexture = LoadImage(filePath);

	// Create a rectangle to hold the frames
	animationClips = new SDL_Rect[frames];

	// Init the calculated frames to 0
	totalFrames = 0;

	// Get the animationRate parameter
	animationRate = animRate;

	// Clip frames by dividing the image size with the frames
	// it contains
	for (int iRows = 0; iRows <= frameRows; iRows++)
	{
		for (int i = 0; i != frames; i++) {

			SDL_QueryTexture(animationTexture, NULL, NULL, &animationClips[i].w, &animationClips[i].h);
			if (frameRows > 1)
				animationClips[i].h = animationClips[i].h / iRows;

			animationClips[i].w = animationClips[i].w / frames;
			
			animationClips[i].x = animationClips[i].w * i;
			animationClips[i].y = animationClips[i].h * iRows;

			// Add a counted frame to the total
			totalFrames++;
		}
	}
	
	// Splitting the sheet causes makes one empty
	// frame, so remove that index
	totalFrames--;

	// Initialize the start frame and start time
	currentFrame = 0;
	animationTime = SDL_GetTicks();
	framesPlayed = 0;
}

bool Animation::playAnimation() {
	
	// Draw the animation with the calculated frame
	ApplySurface(x,y, animationTexture, &animationClips[currentFrame]);

	// Calculate the frame that we need to draw
	if (SDL_GetTicks() > (animationTime + (animationRate * 10))) {
	
		if (currentFrame == totalFrames)
			currentFrame = 0;
		else
			currentFrame++;

		
		animationTime = SDL_GetTicks();
	}
	
	if (framesPlayed < currentFrame)
		framesPlayed = currentFrame;
	

	return true;
}

bool Animation::playAnimationOnce() {
	if (animationPlaying()) {
		playAnimation();
		return false;
	}
	else {
		return true;
	}
}

bool Animation::scrollAnimation(scrollDirection scrollDir) {
	
	// Create a second identical texture, and position variables
	int loopX, loopY;

	// Store texture height and width
	int textureH, textureW;
	SDL_QueryTexture(animationTexture, NULL, NULL, &textureW, &textureH);

	// Variable needed to count where to move the animation
	// we use either -1 or 1 as a multiplier and check
	// up & down together and left & right together
	int directionMultiplier = 0;

	// Checks the scroll direction and sets the second
	// scrolling texture adjacent to the first one
	switch(scrollDir) {
	case UP:
		loopX = x;
		loopY = y - textureH;
		directionMultiplier = -1;
		break;
	case DOWN:
		loopX = x;
		loopY = y + textureH;
		directionMultiplier = 1;
		break;
	case LEFT:
		loopX = x + textureW;
		loopY = y;
		directionMultiplier = -1;
		break;
	case RIGHT:
		loopX = x - textureW;
		loopY = y;
		directionMultiplier = 1;
		break;
	default:
		break;
	};
	
	// Draw the first part of the animation
	ApplySurface(x,y,animationTexture, &animationClips[0]);
	// Draw the second part adjacent to the first texture
	ApplySurface(loopX,loopY,animationTexture, &animationClips[0]);

	// Update the location of the animation
	// for the scrolling effect, here we use the multiplier
	if (scrollDir == UP || scrollDir == DOWN)
		y += directionMultiplier * ((SDL_GetTicks() - animationTime) * animationRate / 100);

	else if (scrollDir == LEFT || scrollDir == RIGHT)		
		x += directionMultiplier * ((SDL_GetTicks() - animationTime) * animationRate / 100);
	
	
	// Check that the texture doesn't go out of bounds
	// vertically
	if ( y > textureH)
		y -= textureH;
	else if ( y < (textureH * -1))
		y += textureH;

	// Check that the texture doesn't go out of bounds
	// horizontally
	if ( x > textureW) {
		x -= textureW;
	}
	else if ( x < (textureW * -1)) {
		x += textureW;
	}
	animationTime = SDL_GetTicks();
	return true;
}

Animation::~Animation(void)
{
}

// Check if the animation is still playing
bool Animation::animationPlaying() {
	if (framesPlayed < totalFrames) {
		return true;
	}
	else {
		return false;
	}
}