#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "draw.h"
#include "file.h"

#include "SDL.h"

class gameObject
{	
	public:
		SDL_Texture* objectTexture;
		
		bool deleteThis;

		int x, y;
		int xVelocity, yVelocity;
		int maxSpeed;

		SDL_Rect collisionBox;

		// Collision buffer - makes collision boxes
		// smaller by its value by pixel
		int collisionBuffer;
		bool collisionEnabled;

		gameObject(void);
		~gameObject(void);
		
		bool checkCollision(gameObject* collObject);
		virtual int collisionEvent();
		int drawObject();
		virtual int updatePosition();
};

#endif