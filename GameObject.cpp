#include "GameObject.h"



GameObject::GameObject(Mesh mesh, glm::vec2 dimensions, GameObjectType type, glm::vec3 position, std::string texturePath)
{
	m_type = type; // Set the type
	m_mesh = mesh; // Create a new mesh for the game object
	transform = Transform(position); // Set the position of the mesh
	texture = new Texture(texturePath); // Texture for object

	m_dimensions = dimensions;

	// Store bounding box size and coordinates
	aabb = AABB(glm::vec2(position.x + dimensions.x / 2, position.y + dimensions.y / 2), glm::vec2(dimensions.x / 2, dimensions.y / 2));

	id = gameObjects.size(); // Store the ID based on the size of vector
	gameObjects.push_back(this);
}


GameObject::~GameObject()
{

}


GLvoid GameObject::Update(GLfloat deltaTime)
{
	aabb.m_halfSize = glm::vec2(m_dimensions.x * transform.GetScale().x / 2, m_dimensions.y * transform.GetScale().y / 2);
	aabb.m_center = glm::vec2(transform.GetPos().x + aabb.m_halfSize.x, transform.GetPos().y + aabb.m_halfSize.y);
	
}


GLvoid GameObject::Draw(Camera& camera)
{
	texture->Bind(); // Bind to texture for drawing
		m_mesh.Draw(transform, camera); // Draw mesh within provided camera and draw using bound texture
	texture->Unbind(); // Unbind from texture
}

vector<GameObject*> GameObject::gameObjects; // All the game objects in the game