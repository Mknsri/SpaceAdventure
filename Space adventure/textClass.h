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
		SDL_Surface* textSurface;
		
		
		SDL_Color textColor;


		TTF_Font *font;

	public:
		textClass(SDL_Color color);
		~textClass(void);

		int collisionEvent();
		std::string textMessage;
		void setMessage(std::stringstream &message);
};

#endif