#pragma once

#include "Bullet.h"

class Invader : public GameObject
{
public:
	// Members
	GLfloat speed = 1.f;
	GLboolean death = false;

	// Methods
	Invader();
	virtual ~Invader();

	GLvoid Fire(BulletDirection direction); // Fires
	GLvoid Death(); // Initiates the death sequence

	virtual void Update(GLfloat deltaTime); // Updates Invader logic

private:

};

#pragma once
