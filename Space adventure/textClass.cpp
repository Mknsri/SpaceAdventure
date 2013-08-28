#include "textClass.h"


textClass::textClass() {
	// Init SDL TTF
	if (TTF_Init() == -1) {
		std::cout << TTF_GetError() << std::endl;
	}
	
	// Default position
	x = 1;
	y = 1;

	// Open font
	font = nullptr;
	font = TTF_OpenFont("data\\font.ttf", 15);
	
	// Null the object texture
	objectTexture = nullptr;

	// Check if font was opened
	if (font == nullptr)
        throw std::runtime_error("Failed to load font");
	
	// Default font color ( white )
	SDL_Color color = {255,255,255};
	textColor = color;

	// Unflag for deletion
	deleteThis = false;

	// By default, text does not collide
	collisionBuffer = 0;
	collisionEnabled = false;

}

void textClass::setMessage(std::stringstream &message, bool appendText) {

	// If were not appending text, set the message to empty
	if (!appendText)
		textMessage = "";

	// Set the message from parameter
	textMessage = message.str();
	
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    textSurface = TTF_RenderText_Blended(font, textMessage.c_str(), textColor);
    objectTexture = surfaceIntoTexture(textSurface);
}

textClass::~textClass(void)
{
	// Close TTF font
    TTF_CloseFont(font);

}

int textClass::collisionEvent() {
	// No collision actions 
	return 0;
}