#include "AABB.h"



AABB::AABB(glm::vec2 center, glm::vec2 halfSize)
{
	m_center = center;
	m_halfSize = halfSize;
}


AABB::~AABB()
{
}

bool AABB::Intersects(AABB b)
{
	if (abs(this->m_center.x - b.m_center.x) < this->m_halfSize.x + b.m_halfSize.x)
	{
		if (abs(this->m_center.y - b.m_center.y) < this->m_halfSize.y + b.m_halfSize.y)
		{
			return true;
		}
	}

	return false;
}