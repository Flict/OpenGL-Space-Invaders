#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;

class Texture
{
public:
	Texture(); // Default constructor
	Texture(const std::string& fileName);

	void Bind(); // Set OpenGL up to bind texture
	void Unbind(); // Unbind a texture

	virtual ~Texture();
protected:
private:
	GLuint m_texture; // Holds the handle to the texture
};

