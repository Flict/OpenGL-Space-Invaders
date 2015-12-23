#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include "camera.h"

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->m_pos = pos;
		this->m_rot = rot;
		this->m_scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_pos); // Translation matrix
		glm::mat4 scaleMatrix = glm::scale(m_scale); // Rotation matrix
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1.0, 0.0, 0.0)); // Rotation x Matrix
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0.0, 1.0, 0.0)); // Rotation y Matrix
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0.0, 0.0, 1.0)); // Rotation z Matrix
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(glm::vec3& pos) { this->m_pos = pos; }
	inline void SetRot(glm::vec3& rot) { this->m_rot = rot; }
	inline void SetScale(glm::vec3& scale) { this->m_scale = scale; }
protected:
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

