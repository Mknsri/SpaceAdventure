#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include "draw.h"
#include "gameObject.h"

#include "SDL_ttf.h"

#include <string>
#include <sstream>

class textClass : public gameObject
{
	private:
		// Needed to transform TTF to texture
		SDL_Surface* textSurface;
		
		// Text color, default set in constructor
		SDL_Color textColor;

		// Font pointer
		TTF_Font *font;

	public:
		textClass();
		~textClass(void);

		// handles collisions for object
		int collisionEvent();

		// Holds the current message
		std::string textMessage;

		// Sets the message, second parameter appends the text to existing
		// message if true (default false)
		void setMessage(std::stringstream &message, bool appendText = false);
};

#endif