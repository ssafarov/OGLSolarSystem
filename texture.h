#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

#include <Windows.h>
#include "Libraries\glew\GL\glew.h"
#include "Libraries\freeglut\GL\freeglut.h"
#include "Libraries\glaux\GL\glaux.h"

#include "globals.h"

// define the header structure for
// loading the TGA header info.
#pragma pack(1) // pack it so that I can have shorts & chars in sequence and read directly from file memory
struct TGAHeader {
	char    id_length;
	char    map_type;
	char    type;
	short   map_start;
	short   map_length;
	char    map_depth;
	short   x_origin;
	short   y_origin;
	short   width;
	short   height;
	char    bpp;
	char    descriptor_bits;
};
#pragma pack()


// Class for texture image files for OpenGL textures
class Texture
{
private:
	std::string tgaAllowed = "tga";
	std::string bmpAllowed = "bmp";

	GLuint textureHandle;	// the handle for the texture in OpenGL

	char *ptrTexturePixels, *ptrTextureBuffer;

	FILE *ptrFile;	// Texture file handle
	std::string textureFileExt; // Texture file extension

	void LoadTGATexture(FILE *ptrTextureFile);
	void LoadBMPTexture(FILE *ptrTextureFile);

public:
	// Constructs and loads a TGA into OpenGL from the given image file path
	Texture(char* imagePath);

	// Returns the handle to the texture created from the image, for binding to OpenGL
	GLuint getTextureHandle(void);
};
