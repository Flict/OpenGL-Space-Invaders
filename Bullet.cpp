#include "Bullet.h"

const GLfloat vertices[] = {
	// Body - Front Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.5f, 0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 

};

const GLuint indices[] = {
	0, 1, 2, // Body - Front Left triangle
	3, 2, 1, // Body - Front Right triangle
};


Bullet::Bullet(BulletDirection direction) : GameObject(Mesh(vertices, sizeof(vertices), indices, sizeof(indices)), glm::vec2(1.f, 1.f), GameObjectType::bullet, glm::vec3(0.f, 0.f, 0.f), defaultTexture)
{
	yDirection = direction; // Store the direction of the bullet

	transform.SetScale(glm::vec3(.01f, .03f, .1f));

//	activeBullets.push_back(this);
}


Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime); // Parent class update
	
	if (!explosionAnim)
	transform.GetPos().y -= deltaTime * (speed * yDirection);
	
	if (transform.GetPos().y > 1.f || transform.GetPos().y < -1.f)
		GameObject::gameObjects.erase(std::remove(GameObject::gameObjects.begin(), GameObject::gameObjects.end(), this), GameObject::gameObjects.end());

	for (std::vector<int>::size_type i = 0; i != GameObject::gameObjects.size(); i++)
	{
		if (GameObject::gameObjects[i]->m_type == GameObjectType::invader)
		{
			if (aabb.Intersects(GameObject::gameObjects[i]->aabb) && !explosionAnim)
			{
				cout << "Bullet Intersection with invader with object id: " << i << endl;

				explosion = new Explosion(transform.GetPos());
				explosionAnim = true;
				GameObject::gameObjects.erase(GameObject::gameObjects.begin() + i);
			}

		}

		if (i >= GameObject::gameObjects.size())
			break;

	}
	
	if (explosionAnim)
	{
		if (timeAlive < LIFE_SPAN)
			explosion->Update(deltaTime);	
		else
		{
			for (std::vector<int>::size_type i = 0; i != GameObject::gameObjects.size(); i++)
			{
				if (i >= GameObject::gameObjects.size())
					break;
				if (GameObject::gameObjects[i]->m_type == GameObjectType::particle)
					GameObject::gameObjects.erase(std::remove(GameObject::gameObjects.begin(), GameObject::gameObjects.end(), GameObject::gameObjects[i]), GameObject::gameObjects.end());
			}

			GameObject::gameObjects.erase(std::remove(GameObject::gameObjects.begin(), GameObject::gameObjects.end(), this), GameObject::gameObjects.end());
			explosionAnim = false;
		}

		timeAlive += deltaTime;
	}
	
}

GLvoid Bullet::Draw(Camera& camera)
{
	if (!explosionAnim)
	GameObject::Draw(camera); // Parent class draw
}
	

	

//vector<Bullet*> Bullet::activeBullets; // Active bullets in game