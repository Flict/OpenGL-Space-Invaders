#include "AABB.h"



AABB::AABB(glm::vec2 center, glm::vec2 halfSize)
{
	m_center = center;
	m_halfSize = halfSize;
}


AABB::~AABB()
{
}

bool AABB::Intersects(AABB a, AABB b)
{
	if (abs(a.m_center.x - b.m_center.x) < a.m_halfSize.x + b.m_halfSize.x)
	{
		if (abs(a.m_center.y - b.m_center.y) < a.m_halfSize.y + b.m_halfSize.y)
		{
			return true;
		}
	}

	return false;
}