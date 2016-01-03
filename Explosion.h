#pragma once

#include "Particle.h"

class Explosion
{
public:
	// Members
	vector<Particle*> parts; // Parts of the explosion
	GLfloat speed = 4.0f; // Speed of explosion animation
	const GLfloat LIFE_SPAN = 0.2f; // The amount of time to wait before destroying particles
	GLfloat timeAlive = 0.f; // The amount of time the particles have been alive

	// Methods
	Explosion(glm::vec3 position);
	virtual ~Explosion();
	GLvoid Update(GLfloat deltaTime);

private:

};
