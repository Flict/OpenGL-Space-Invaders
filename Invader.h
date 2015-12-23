#pragma once

#include "GameObject.h"

class Invader : public GameObject
{
public:
	// Members
	GLfloat speed = 5.f;

	// Methods
	Invader();
	virtual ~Invader();

private:

};

#pragma once
