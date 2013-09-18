#include "player.h"

playerClass::playerClass() {

	// Load the textures for player
	objectTexture = LoadImage("data\\kalalus.png");
	playerHealthIcon = LoadImage("data\\health.png");

	// Load player animations
	playerAnimIdle = new Animation("data\\kalalus_idle2.png",10);
	playerAnimHurt = new Animation("data\\kalalus_hurt.png",4);
	playerAnimDeath = new Animation("data\\kalalus_death.png",8);

	// Set player health
	health = 3;
	alive = true;

	// Collisionbuffer, the pixel amount the collisionbox 
	// is feathered from the actual texture size
	collisionBuffer = 10;

	// Init position
	x = 35;
	y = 35;

	objectType = "player";

	// Animation position
	playerAnimIdle->x = x;
	playerAnimIdle->y = y;
	 
	// Init speed
	xVelocity = 0;
	yVelocity = 0;

	// Disable player fire in title screen
	fireDisabled = true;

	// Set object not to be deleted
	deleteThis = false;

	// Max speed
	maxSpeed = 5;
	
	// Enable collision
	collisionEnabled = true;
	collisionDetected = false;


	// Set score
	score = 10;
	
	scoreText = new textClass();


}

void playerClass::playerFire() {
};

int playerClass::updatePosition() {
	
	// Out of bounds check
	if (x > SCREEN_WIDTH - 30 )
		x = SCREEN_WIDTH - 30;
	if (x < 20)
		x = 20;
	
	// Set speed
	x += xVelocity * maxSpeed;

	// Out of bounds check
	if (y > SCREEN_HEIGHT - 30 )
		y = SCREEN_HEIGHT - 30;
	if (y < 20)
		y = 20;
	
	// Set speed
	y += yVelocity * maxSpeed;

	// Set animation position
	playerAnimIdle->x = x;
	playerAnimIdle->y = y;
	playerAnimHurt->y = y;
	playerAnimHurt->x = x;

	// collision behaviour
	if (collisionDetected && (SDL_GetTicks() < collisionTime + 700)) {
		collisionEnabled = false;
	} else if (collisionDetected && (SDL_GetTicks() > collisionTime + 700)) {
		if (health > 0) {
			collisionEnabled = true;
		}
		collisionDetected = false;
	}

	return 0;
}

// Collision event
int playerClass::collisionEvent()  {

	collisionTime = SDL_GetTicks();
	collisionDetected = true;

	if (health > 0) {
		health--;
	}

	return 0;
}

int playerClass::drawObject() {

	// Play animations
	if (collisionDetected) {
		playerAnimHurt->playAnimation();
		if (health == 0) {
			collisionEnabled = false;
		}
	} 
	else if(health == 0) {
		playerDeath();
	} 
	else {
		playerAnimIdle->playAnimation();
	}
	
	// Draw health
	for (int i = 0; i != health; i++) {
		ApplySurface(i * 20, 10, playerHealthIcon);
	}

	return 0;
}

bool playerClass::isPlayerAlive() {
	if (alive == false) {
		return false;
	} else {
		return true;
	}
}

void playerClass::playerDeath() {
	collisionEnabled = false;
	// Wait for the animation play
	playerAnimDeath->x = x-25;
	playerAnimDeath->y = y-50;
	if (playerAnimDeath->playAnimationOnce()) {
		alive = false;
	}


}

void playerClass::newGame() {
	// Set player health
	health = 3;
	alive = true;

	// Init position
	x = 35;
	y = 35;

	// Reset animations
	playerAnimIdle->x = x;
	playerAnimIdle->y = y;
	 
	playerAnimDeath->framesPlayed = 0;

	// Init speed
	xVelocity = 0;
	yVelocity = 0;

	// Disable player fire in title screen
	fireDisabled = true;

	// Enable collision
	collisionEnabled = true;
	collisionDetected = false;

}

void playerClass::displayScore() {

	std::stringstream scoreStream;
	scoreStream.str("");	
	scoreStream << score;
	
	scoreText->setMessage(scoreStream);
	scoreText->y = 10;
	scoreText->x = SCREEN_WIDTH - 50;

	scoreText->drawObject();

}

void playerClass::addScore(int points) { 
	score += points;
}