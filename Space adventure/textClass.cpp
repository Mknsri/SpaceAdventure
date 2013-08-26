#include "textClass.h"


textClass::textClass(SDL_Color color) {
	// Init SDL TTF
	if (TTF_Init() == -1) {
		std::cout << TTF_GetError() << std::endl;
	}

	font = nullptr;
	font = TTF_OpenFont("C:\\Users\\make\\Documents\\font.ttf", 15);
	
	objectTexture = nullptr;

	if (font == nullptr)
        throw std::runtime_error("Failed to load font");
	
	textColor = color;

	deleteThis = false;

	collisionBuffer = 0;
	collisionEnabled = false;

}

void textClass::setMessage(std::stringstream &message) {
	textMessage = message.str();
	
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    textSurface = TTF_RenderText_Blended(font, textMessage.c_str(), textColor);
    objectTexture = surfaceIntoTexture(textSurface);
}

textClass::~textClass(void)
{
	
    TTF_CloseFont(font);

}

int textClass::collisionEvent() {
	return 0;
}