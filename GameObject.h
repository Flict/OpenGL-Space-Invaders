#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "AABB.h"

enum GameObjectType // types of game object
{
	player = 0,
	invader = 1,
	bullet = 2,
	square = 3,
	particle = 4
};

static std::string defaultTexture = "./assets/white-texture.bmp";
class GameObject
{
public:
	GameObject(Mesh mesh, glm::vec2 dimensions, GameObjectType type, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), std::string texturePath = defaultTexture); // Constructor
	virtual ~GameObject();

	static vector<GameObject*> gameObjects; // All the game objects in the game
	Transform transform; // Objects Transformations
	Texture* texture; // Objects texture
	Mesh m_mesh; // Objects Mesh
	AABB aabb; // Collision bounding box

	GLint id; // ID of this game object
	GameObjectType m_type; // Type is used to give useful information to an object, like what it is. "Player, Invader, Bullet" etc

private:
	glm::vec2 m_dimensions;
	
public:
	virtual GLvoid Update(GLfloat deltaTime);
	virtual GLvoid Draw(Camera& camera);
};

