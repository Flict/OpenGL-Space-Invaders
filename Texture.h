#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;

enum TextureType
{
	Bitmap = 0,
	Font = 1
};

class Texture
{
public:
	Texture(); // Default constructor
	Texture(const std::string& fileName, TextureType textureType = TextureType::Bitmap, std::string text = "");

	void Bind(); // Set OpenGL up to bind texture
	void Unbind(); // Unbind a texture

	virtual ~Texture();
protected:
private:
	GLuint m_texture; // Holds the handle to the texture
};

