#pragma once

#include "Explosion.h"


enum BulletDirection // Possible bullet directions
{
	UP = -1,
	DOWN = 1
};

class Bullet : public GameObject
{
public:
	// Members
	GLfloat speed = 20.f;
	GLint yDirection = 1; // The direction the bullet is travelling -1 = UP, 1 = DOWN
	Explosion* explosion;
	GLboolean explosionAnim = false;
	const GLfloat LIFE_SPAN = 0.5f; // The amount of time to wait before destroying particles
	GLfloat timeAlive = 0.f; // The amount of time the particles have been alive

	static GLint SCORE;
	// Methods
	Bullet(BulletDirection direction);
	virtual ~Bullet();

	virtual void Update(GLfloat deltaTime); // Updates bullet logic
	virtual void Draw(Camera& camera); // Updates bullet logic

	//static vector<Bullet*> activeBullets; // All bullets active in game

private:

};

#pragma once
