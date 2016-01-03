#include "Square.h"

const GLfloat vertices[] = {
	// Body - Front Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Left 0
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Left 1
	0.5f, 0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Front Top Right 2
	0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Right 3
};

const GLuint indices[] = {
	0, 1, 2, // Body - Front Left triangle
	3, 2, 1, // Body - Front Right triangle
};


Square::Square() : GameObject(Mesh(vertices, sizeof(vertices), indices, sizeof(indices)), glm::vec2(1.f, 1.f), GameObjectType::square, glm::vec3(0.f, 0.f, 0.f))
{

}


Square::~Square()
{
}