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

		// Type for collision ignoring
		std::string objectType;

		// power up settings - only used by player
		// but defined in gameobject since im dumb
		int activePowerUps;
		
		enum powerUps {
			POWERUP_MULTIFIRE = 0x01,
			POWERUP_TRIAMMO = 0x02,
		};

		Uint32 pupStartTime;
		Uint32 pupStartTime2;

		// Point worth
		int pointWorth;

		// Position integers
		int x, y;
		
		int health;

		// Speed integers
		int xVelocity, yVelocity;
		int maxSpeed;
		
		// Rectangle to hold height and width
		SDL_Rect collisionBox;
		// If using animations, need manual collision box size
		int collBoxH, collBoxW;

		// Collision buffer - makes collision boxes
		// smaller by its value by pixel
		int collisionBuffer;
		bool collisionEnabled;

		gameObject(void);
		~gameObject(void);
		
		// Check collision with this object and parameter object
		bool checkCollision(gameObject* collObject);
		
		// Custom collision, if enabled, need to set collisionbox using collisionbox.h / .w
		bool customCollision;

		// Checked if collision returns true
		virtual int collisionEvent();

		// Draws object
		virtual int drawObject();

		// Update per frame
		virtual int updatePosition();
		
		// Add to players score
		virtual void addScore(int points);

		virtual void getObject(gameObject* obj);
		virtual void setTarget(int targetY);
		virtual void setPowerUp(powerUps powerup);
		virtual bool checkPowerUp(powerUps powerup);
		
};

#endif