#include "player.h"

playerClass::playerClass() {

	// Load the textures for player
	objectTexture = nullptr;
	playerHealthIcon = LoadImage("data\\health.png");

	// Load player animations
	playerAnimIdle = new Animation("data\\kalalus_idle2.png",10);
	playerAnimHurt = new Animation("data\\kalalus_hurt.png",4);
	playerAnimDeath = new Animation("data\\kalalus_death.png",8);

	// Set player health
	health = 3;
	alive = true;

	// Collision box
	customCollision = true;
	collBoxH = 50;
	collBoxW = 70;

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
	maxSpeed = 6;
	
	// Enable collision
	collisionEnabled = true;
	collisionDetected = false;


	// Set score
	score = 0;
	
	scoreText = new textClass();

	pupStartTime = 0;
	pupStartTime2 = 0;


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

	// Draw score
	this->displayScore();

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

	// Stop the player
	xVelocity = 0;
	yVelocity = 0;



}

void playerClass::newGame() {
	// Set player health
	health = 3;
	alive = true;

	// Init position
	x = 30;
	y = 200;

	// Reset animations
	playerAnimIdle->x = x;
	playerAnimIdle->y = y;
	 
	playerAnimDeath->framesPlayed = 0;

	// Init speed
	xVelocity = 0;
	yVelocity = 0;

	score = 0;

	// Enable player
	fireDisabled = false;

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

void playerClass::setPowerUp(powerUps powerup) {

	if (powerup & gameObject::POWERUP_TRIAMMO) {
		activePowerUps |= powerup;
		if (pupStartTime == 0) {
			pupStartTime = SDL_GetTicks() + 10000;
		}
		else {
			pupStartTime += 10000;
		}
	}
	else if (powerup & gameObject::POWERUP_MULTIFIRE) {
		activePowerUps |=  powerup;
		if (pupStartTime2 == 0) {
			pupStartTime2 = SDL_GetTicks() + 10000;
		}
		else {
			pupStartTime2 += 10000;
		}
		
	}
}

bool playerClass::checkPowerUp(powerUps powerup) {
	if(powerup & POWERUP_TRIAMMO) {
		if (activePowerUps & powerup && pupStartTime > SDL_GetTicks()) {
			return true;
		}
		else {
			// if check fails, remove the bit flag
			activePowerUps = activePowerUps & ~powerup;
			return false;
		}
	}
	else if (powerup & POWERUP_MULTIFIRE) {
		if (activePowerUps & powerup && pupStartTime2 > SDL_GetTicks()) {
 			return true;
		}
		else {
			// if check fails, remove the bit flag
			activePowerUps = activePowerUps & ~powerup;
			return false;
		}
	}

	return false;
}