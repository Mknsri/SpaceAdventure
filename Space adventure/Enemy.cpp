#include "Enemy.h"


Enemy::Enemy(enemyType eType, int startY)
{
	// Death animation
	explosionAnim = new Animation("data\\explosionanim.png",5,0,6);

	pointWorth = 0;

	objectType = "enemy";

	// Enemytype enum for switches
	enType = eType;

	switch (enType) 
	{
		case MORP:
			objectTexture = LoadImage("data\\morp.png");
			pointWorth = 10;
		break;
		case DORP:
			objectTexture = LoadImage("data\\dorp.png");
			pointWorth = 20;
		break;
		case BENE:
		break;
		case MONSTRO:
		break;

		default: break;
	}

	
	y = startY;

	// If starting height was not specified
	if (y == 0) {
		std::random_device rng;
		y = rng() % 460;

	}

	x = 690;
	maxSpeed = 5;

	collisionBuffer = 5;
	collisionEnabled = true;
	collisionDetected = false;
}


Enemy::~Enemy(void)
{
}


int Enemy::updatePosition() {


	// Movement by enemytype
	switch (enType)
	{
	case Enemy::MORP:
		
		// Do wave motion
		y = morpMotion.waveMotion(y,20,30);

		// Move enemy to the left
		x -= 4;
		break;
	case Enemy::DORP:

		// Move enemy to the left
		x -= 5;
		break;
	case Enemy::BENE:
		break;
	case Enemy::MONSTRO:
		break;
	default:
		break;
	}

	// if out of bounds, delete object
	if (x < -40) {
		deleteThis = true;
	}

	// Collision explosion
	if (explosionAnim->animationPlaying() && collisionDetected == true) {
		collisionEnabled = false;
		objectTexture = nullptr;
		explosionAnim->x = x-20;
		explosionAnim->y = y-20;
		explosionAnim->playAnimationOnce();
	}
	else if ( explosionAnim->animationPlaying() == false && collisionDetected == true)
		deleteThis = true;

	return 0;
}

int Enemy::collisionEvent() {
	
	collisionDetected = true;
	return 0;
}