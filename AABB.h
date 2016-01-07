#pragma once
#include "graphics_dependencies\glm\glm\glm.hpp"
class AABB
{
public:
	// Members
	glm::vec2 m_center, m_halfSize;

	// Methods
	AABB() {};
	AABB(glm::vec2 center, glm::vec2 halfSize);
	~AABB();

	bool Intersects(AABB b);
};

