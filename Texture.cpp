#include "Texture.h"
#include "SDL.h"
#include <iostream>

Texture::Texture()
{

}

Texture::Texture(const std::string& fileName)
{
	SDL_Surface* image = SDL_LoadBMP(fileName.c_str());

	if (image == NULL) // If a valid image did not load
	{
		cerr << "Failed to load texture: " << fileName << endl; // Output a console error
	}

	glGenTextures(1, &m_texture); // Generate space for texture and store the handle to it
	glBindTexture(GL_TEXTURE_2D, m_texture); // Bind to this texture for drawing

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap the texture on the X axis when out of bounds of 0 to 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap the texture on the Y axis when out of bounds of 0 to 1

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // When the image takes up fewer pixels than it's size, linearly interpolate the image using it's own existing pixels
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // When the image takes up more pixels than it's size, linearly interpolate the image using it's own existing pixels
	glTexImage2D(GL_TEXTURE_2D, 0, image->format->BytesPerPixel, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels); // Set the image and it's properties to use
	SDL_FreeSurface(image); // Free memory
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture); // Delete the texture to free memory
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture); // Bind a texture to a texturing target
} 

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind a texture from a texturing target
}