#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Player : public GameObject
{
public:
	// Members
	GLfloat speed = 10.f;

	// Methods
	Player();
	virtual ~Player();

	void Fire(BulletDirection direction);

private:
	
};

