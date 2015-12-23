#include "Mesh.h"

Mesh::Mesh(const std::string fileName)
{

}

Mesh::Mesh()
{

}

Mesh::Mesh(const float vertexPositions[], GLint size, const unsigned int indices[], GLint numIndices)
{
	for (int i = 0; i < size; i++)
	{
		m_vertexPositions[i] = vertexPositions[i];
	}

	for (int i = 0; i < numIndices; i++)
	{
		m_indicesPositions[i] = indices[i];
	}

	m_pShader = new Shader("./assets/shader"); // Store the shader to use for drawing

	LoadAssets();
}


Mesh::~Mesh()
{
}

void Mesh::InitializeVertexBuffer()
{
	glGenBuffers(1, &m_positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexPositions), m_vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	cout << "positionBufferObject created OK! GLUint is: " << m_positionBufferObject << endl;
}

void Mesh::LoadAssets()
{
	//initializeProgram(); //create GLSL Shaders, link into a GLSL program

	InitializeVertexBuffer(); //load data into a vertex buffer

	glGenVertexArrays(1, &m_vao); //create a Vertex Array Object
	glBindVertexArray(m_vao); //make the VAO active

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indicesPositions), m_indicesPositions, GL_STATIC_DRAW);

	cout << "Vertex Array Object created OK! GLUint is: " << m_vao << std::endl;

	cout << "Loaded Assets OK!\n";
}

void Mesh::Draw(Transform& transform, Camera& camera, bool cullBack)
{
	if (cullBack)
		glCullFace(GL_BACK);
	else
		glCullFace(GL_FRONT);
	glUseProgram(m_pShader->m_program); //installs the program object specified by program as part of current rendering state

									 //load data to GLSL that **may** have changed
	//glUniform2f(shader.m_offsetLocation, m_offsetX, m_offsetY);
	glm::mat4 modelViewMatrix = camera.GetProjection() * camera.GetView() * transform.GetModel();
	glUniformMatrix4fv(m_pShader->m_modelTransformLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject); //bind positionBufferObject
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo); //bind

	glEnableVertexAttribArray(m_pShader->m_positionLocation); // Enable the attribute to use for positioning
	glEnableVertexAttribArray(m_pShader->m_colourLocation); // Enable the attribute to use for colour
	glEnableVertexAttribArray(m_pShader->m_textureCoord); // Enable the attribute to use for colour
														   

	glVertexAttribPointer(m_pShader->m_positionLocation, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), 0); //define **how** values are reader from positionBufferObject in Attrib 0
	glVertexAttribPointer(m_pShader->m_colourLocation, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float))); //define **how** values are reader from positionBufferObject in Attrib 0
	glVertexAttribPointer(m_pShader->m_textureCoord, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float))); //define **how** values are reader from positionBufferObject in Attrib 0


	glDrawElements(GL_TRIANGLES, sizeof(m_indicesPositions), GL_UNSIGNED_INT, 0); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle

	glDisableVertexAttribArray(m_pShader->m_positionLocation); //cleanup
	glDisableVertexAttribArray(m_pShader->m_colourLocation); //cleanup
	glDisableVertexAttribArray(m_pShader->m_textureCoord); //cleanup
	glUseProgram(0); //clean up

}

void Mesh::Update(double deltaTime) //update simulation with an amount of time to simulate for (in seconds)
{
	m_offsetX += m_offsetXSpeed * deltaTime;
	m_offsetY += m_offsetYSpeed * deltaTime;
}
