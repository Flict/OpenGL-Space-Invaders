#include "Player.h"

const GLfloat vertices[] = {
	// Body - Front Face
	-0.5f, 0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.5f, -0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.5f, 0.5f, 0.5f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.5f, -0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 3

	// Turret - Front Face
	-0.1f, 1.2f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.1f, 0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.1f, 1.2f, 0.5f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.1f, 0.5f, 0.5f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 3
	
};

const GLuint indices[] = {
	0, 1, 2, // Body - Front Left triangle
	3, 2, 1, // Body - Front Right triangle

	4, 5, 6, // Turret - Front Left Triangle
	7, 6, 5 //	Turret - Front Right Triangle
};


Player::Player() : GameObject(Mesh(vertices, sizeof(vertices), indices, sizeof(indices)), glm::vec2(1.f, 1.7), GameObjectType::player, glm::vec3(0.f , 0.f , 0.f))
{

}


Player::~Player()
{
}

GLvoid Player::Fire(BulletDirection direction)
{
	Bullet* bullet = new Bullet(direction);
	bullet->transform.GetPos() = this->transform.GetPos();
}