#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

#include <Windows.h>
#include <GL\glut.h>

// Class for texture image files for OpenGL textures
class Texture
{
private:
	// the handle for the texture in OpenGL
	GLuint textureHandle;
public:
	// Constructs and loads a TGA into OpenGL from the given image file path
	Texture(char* imagePath);

	// Returns the handle to the texture created from the image, for binding to OpenGL
	GLuint getTextureHandle(void);
};
