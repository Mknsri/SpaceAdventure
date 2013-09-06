#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "draw.h"

#include "SDL.h"

// Wrapper object for all game objects
class gameObject
{	
	public:
		// Object-texture, loaded in constructor
		SDL_Texture* objectTexture;
		
		// Flag for deleting the object in the next frame
		bool deleteThis;

		// Flag for detected collision
		bool collisionDetected;
		Uint32 collisionTime;

		// Position integers
		int x, y;

		// Speed integers
		int xVelocity, yVelocity;
		int maxSpeed;
		
		// Rectangle to hold height and width
		SDL_Rect collisionBox;

		// Collision buffer - makes collision boxes
		// smaller by its value by pixel
		int collisionBuffer;
		bool collisionEnabled;

		gameObject(void);
		~gameObject(void);
		
		// Check collision with this object and parameter object
		bool checkCollision(gameObject* collObject);

		// Checked if collision returns true
		virtual int collisionEvent();

		// Draws object
		virtual int drawObject();

		// Update per frame
		virtual int updatePosition();
};

#endif