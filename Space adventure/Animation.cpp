#include "Animation.h"


Animation::Animation(std::string filePath, int frames, int frameRows, int animRate)
{

	animationTexture = LoadImage(filePath);
	animationClips = new SDL_Rect[frames];
	totalFrames = 0;
	animationRate = animRate;

	// Clip frames
	for (int iRows = 0; iRows <= frameRows; iRows++)
	{
		for (int i = 0; i != frames; i++) {
			SDL_QueryTexture(animationTexture, NULL, NULL, &animationClips[i].w, &animationClips[i].h);
			if (frameRows > 1)
				animationClips[i].h = animationClips[i].h / iRows;

			animationClips[i].w = animationClips[i].w / frames;
			
			animationClips[i].x = animationClips[i].w * i;
			animationClips[i].y = animationClips[i].h * iRows;

			totalFrames++;
		}
	}
	
	currentFrame = 0;
	animationStartTime = SDL_GetTicks();
}

bool Animation::playAnimation() {
	int currentFrame = ((SDL_GetTicks() - animationStartTime) * animationRate / 1000) % totalFrames;
	ApplySurface(x,y, animationTexture, &animationClips[currentFrame]);



	return true;
}


Animation::~Animation(void)
{
}
