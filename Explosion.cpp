#include "Explosion.h"

GLuint explosionGrid[9][13]
{
	{0,1,0,0,1,0,0,0,1,0,0,1,0},
	{0,0,1,0,0,1,0,1,0,0,1,0,0},
	{0,0,0,1,0,1,0,1,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,0,0,0,0,0,0,0,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,1,0,1,0,1,0,0,0},
	{0,0,1,0,0,1,0,1,0,0,1,0,0},
	{0,1,0,0,1,0,0,0,1,0,0,1,0}

};

Explosion::Explosion(glm::vec3 position)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (explosionGrid[i][j] == 1)
			{ 
				Particle* square = new Particle();
				square->transform.SetScale(glm::vec3(.01f, .01f, .01f));
				square->transform.GetPos().y = position.y - (0.011f * i);
				square->transform.GetPos().x = position.x + (0.011f * j);
				parts.push_back(square);
			}
		}
	}
	
}

GLvoid Explosion::Update(GLfloat deltaTime)
{
	for (std::vector<int>::size_type i = 0; i != parts.size(); i++)
	{
		/*parts[i]->transform.GetPos().x -= (sin(i) * deltaTime) + (cos(i) * deltaTime);
		parts[i]->transform.GetPos().y += sin(i) * deltaTime - cos(i) * deltaTime;
*/
		parts[i]->transform.GetPos().x +=  (cos(i) * speed * deltaTime) + (sin(i) * speed * deltaTime);
		parts[i]->transform.GetPos().y -=  (cos(i) * speed * deltaTime) - (sin(i) * speed * deltaTime);
	}
}


Explosion::~Explosion()
{
}