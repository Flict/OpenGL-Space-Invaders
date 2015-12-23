#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include <string>


using namespace std;
const std::string defaultShader = "./assets/shader";

class Mesh
{
public:
	Mesh(const float vertexPositions[], GLint size, const unsigned int indices[], GLint numIndices);
	Mesh(const std::string fileName);
	Mesh(); // Default Constructor
	virtual ~Mesh();
	void InitializeVertexBuffer();
	void LoadAssets();
	void Draw(Transform& transform, Camera& camera, bool cullBack = true);
	void Update(double deltaTime);

	GLfloat m_vertexPositions[1000];
	GLuint m_indicesPositions[1000];
	GLint m_numIndices;

	

	GLuint m_positionBufferObject;
	GLuint m_ebo;
	GLuint m_vao;
	//the offset we'll pass to the GLSL
	double m_offsetX = -0.5; //using different values from CPU and static GLSL examples, to make it clear this is working
	double m_offsetY = -0.5; //NOTE: we could use an array and pass the pointer, to be simpler & more efficent
	double m_offsetXSpeed = 0.2; //rate of change of offsetX in units per second
	double m_offsetYSpeed = 0.2; //rate of change of offsetY in units per second

private:
	Shader* m_pShader; // Pointer to shader used for drawing
	
};

