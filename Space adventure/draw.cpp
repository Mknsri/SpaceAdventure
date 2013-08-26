#include "draw.h"


//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
 
    window = SDL_CreateWindow("Space adventure", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }
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

SDL_Texture* LoadImage(std::string file){
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(renderer, file.c_str());
    if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
    return tex;
}

SDL_Texture* surfaceIntoTexture(SDL_Surface* surface) {
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr)
		throw std::runtime_error("Failed to transform to texture:");

	return texture;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Rect* clip){
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

	if( clip != nullptr )
	{
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

    SDL_RenderCopy(renderer, tex, clip, &pos);
}

void updateScreen() {
	SDL_RenderPresent(renderer);
}

void clearScreen() {
	SDL_RenderClear(renderer);
}
