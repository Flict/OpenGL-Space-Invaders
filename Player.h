#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	// Members
	GLfloat speed = 10.f;

	// Methods
	Player();
	virtual ~Player();

private:
	
};

