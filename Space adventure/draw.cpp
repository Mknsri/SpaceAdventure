#include "draw.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int initSDL() {

	// Init SDL and check for success
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
 
	// Create window and check success
    window = SDL_CreateWindow("Space adventure", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }

	// Create renderer and check for success
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED 
        | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return 4;
	}

	return 0;
}

// Load image from file and returns texture
SDL_Texture* LoadImage(std::string file){

    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(renderer, file.c_str());

	// Check for errors
    if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());

    return tex;
}

// Converts SDL_Surface to SDL_Texture and returns the texture
SDL_Texture* surfaceIntoTexture(SDL_Surface* surface) {
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr)
		throw std::runtime_error("Failed to transform to texture:");

	return texture;
}

// Draw texture on screen
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Rect* clip){

    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

	// If there are no frames,
	// Pull height and width from texture
	if( clip != nullptr )
	{
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

    SDL_RenderCopy(renderer, tex, clip, &pos);
}

// Update screen
void updateScreen() {
	SDL_RenderPresent(renderer);
}

// Clearscreen
void clearScreen() {
	SDL_RenderClear(renderer);
}
