#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "AABB.h"

static std::string defaultTexture = "./assets/white-texture.bmp";

class GameObject
{
public:
	GameObject(Mesh mesh, glm::vec2 dimensions, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), std::string texturePath = defaultTexture); // Constructor
	virtual ~GameObject();

	bool GameObject::CheckCollision(SDL_Rect a, SDL_Rect b); // Checks collisions

	Transform transform; // Objects Transformations
	Texture* texture; // Objects texture
	Mesh m_mesh; // Objects Mesh
	AABB aabb; // Collision bounding box

private:
	glm::vec2 m_dimensions;
	
public:
	GLvoid Update(GLfloat deltaTime);
	GLvoid Draw(Camera& camera);
};

