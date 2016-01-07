#include "Invader.h"

const GLfloat vertices[] = {
	// Body - Front Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.5f, 0.5f, 0.5f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 3

	// Turret - Front Face
	-0.1f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.1f, -1.2f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.1f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.1f, -1.2f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 3

};

const GLuint indices[] = {
	0, 1, 2, // Body - Front Left triangle
	3, 2, 1, // Body - Front Right triangle

	4, 5, 6, // Turret - Front Left Triangle
	7, 6, 5 //	Turret - Front Right Triangle
};


Invader::Invader() : GameObject(Mesh(vertices, sizeof(vertices), indices, sizeof(indices)), glm::vec2(1.f, 1.7), GameObjectType::invader, glm::vec3(0.f, 0.f, 0.f), "./assets/green-pattern.bmp")
{
	
}


Invader::~Invader()
{
}

GLvoid Invader::Fire(BulletDirection direction)
{
	Bullet* bullet = new Bullet(direction);
	bullet->transform.GetPos() = this->transform.GetPos();
}

GLvoid Invader::Death()
{
	death = true;
}

GLvoid Invader::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime); // Parent class update

	/*if (death == true)
		explosion.Update(deltaTime);*/
}