#include "Enemy.h"


Enemy::Enemy(enemyType eType, int startY)
{
	// Death animation
	explosionAnim = new Animation("data\\explosionanim.png",5,0,6);
	pointWorth = 0;

	health = 1;

	targetObjX = 0;
	targetObjY = 0;

	objectType = "enemy";

	// Enemytype enum for switches
	enType = eType;

	switch (enType) 
	{
		case MORP:
			objectTexture = LoadImage("data\\morp.png");
			pointWorth = 10;
			enemyAnim = nullptr;
			collisionBuffer = 5;
		break;
		case DORP:
			objectTexture = LoadImage("data\\dorp.png");
			pointWorth = 20;
			enemyAnim = nullptr;
			collisionBuffer = 5;
		break;
		case BENE:
			objectTexture = nullptr;
			pointWorth = 40;
			enemyAnim = new Animation("data\\bene.png",2,0,12);
			collBoxH = 40;
			collBoxW = 40;
			collisionBuffer = 5;
		break;
		case MONSTRO:
			collisionBuffer = 50;
			
			bossIdle = LoadImage("data\\monstro.png");
			bossHurt = LoadImage("data\\monstro_hurt.png");
			objectTexture = bossIdle;

			health = 10;
		break;

		default: 
			break;
	}

	
	y = startY;

	// If starting height was not specified
	if (y == 0) {
		std::random_device rng;
		y = rng() % 460;

	}

	x = 690;
	maxSpeed = 5;

	collisionEnabled = true;
	collisionDetected = false;
}


Enemy::~Enemy(void)
{
}

int Enemy::drawObject() {

	// Animated enemy
	if (objectTexture == nullptr && enemyAnim != nullptr) {
		enemyAnim->x = x;
		enemyAnim->y = y;
		enemyAnim->playAnimation();
	}
	else {
		ApplySurface(x,y,objectTexture);
	}

	return 0;
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
		x -= 4;
		break;

	case Enemy::BENE:
		// Move towards player vertically
		if (y < targetObjY) {
			y += 2;
		}
		else if (y > targetObjY) {
			y -= 2;
		}

		x -= 6;
		break;

	case Enemy::MONSTRO:
		if (x > 540) {
			x -= 2;
		}
		break;
	default:
		break;
	}

	// if out of bounds, delete object
	if (x < -40 && x > 700) {
		deleteThis = true;
	}

	// Collision explosion for standard enemies
	if (enType != MONSTRO) {
		if (explosionAnim->animationPlaying() && collisionDetected == true) {
			collisionEnabled = false;
			objectTexture = nullptr;
			explosionAnim->x = x-20;
			explosionAnim->y = y-20;
			explosionAnim->playAnimationOnce();
		}
		else if ( explosionAnim->animationPlaying() == false && collisionDetected == true)
			deleteThis = true;
	}
	// Boss explosion
	else {
		if (explosionAnim->animationPlaying() && collisionDetected == true && health > 0) {
			explosionAnim->x = targetObjX;
			explosionAnim->y = targetObjY - 50;
			explosionAnim->playAnimationOnce();
			objectTexture = bossHurt;
		}
		else if ( explosionAnim->animationPlaying() == false && collisionDetected == true && health > 0) {
			explosionAnim->framesPlayed = 0;
			objectTexture = bossIdle;
			collisionDetected = false;
			
			//objectTexture = nullptr;
			//deleteThis = true;
		}

		// Boss death
		else if (health < 1) {
			objectTexture = bossHurt;
			collisionEnabled = false;
			if (y < 800) {
				y += 2;
			}
			else {
				health = -100;
			}
		} 
	}
	
	return 0;
}

int Enemy::collisionEvent() {
	if (enType == MONSTRO) {
		health--;
	}
	collisionDetected = true;
	
	return 0;
}

void Enemy::getObject(gameObject* obj) {

	targetObjY = obj->y;
	targetObjX = obj->x;

}