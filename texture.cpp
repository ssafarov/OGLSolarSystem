/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

#define _CRT_SECURE_NO_DEPRECATE

#include "texture.h"
#include <Windows.h>
#include <GL\glut.h>
#include <cstdio>
#include <cstdlib>

using namespace System::Windows::Forms;

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

Texture::Texture(char* imagePath)
{
	FILE *ptrFile;		// Texture file handle
	TGAHeader header;	// structure for the header info
	char *ptrPixels, *ptrBuffer;

	// column counter, row counter, i loop counters, and bytes per pixel
	int c, r, i, j, bytesPP = 4;
	char n, packetHeader;
	char pixel[4];

	// open the file
	if ((ptrFile = fopen(imagePath, "rb")) == NULL) {
		MessageBox::Show("Unable to find requested texture file");
		exit(1);
	}

	// read the header
	fread(&header, 18, 1, ptrFile);
	
	// bytes per pixel
	bytesPP = header.bpp / 8; 

	ptrPixels = (char*)malloc(bytesPP * header.width * header.height);

	// Decode texture
	// header type 2 is uncompressed RGB data without a color map / palette
	if (header.type == 2)
	{
		// seek to the start of the data
		fseek(ptrFile, header.map_start + header.map_length * bytesPP + 18, SEEK_SET);

		// read the pixel data into a buffer
		ptrBuffer = (char*)malloc(bytesPP * header.width * header.height);
		fread(ptrBuffer, bytesPP, header.width * header.height, ptrFile);

		// plot the pixel data into pixels buffer
		for (c = 0; c < header.width; c++)	// count up columns
		{
			for (r = 0; r < header.height; r++)	// rows
			{
				if (bytesPP == 4)
				{
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 0] = ptrBuffer[(c + r * header.width) * bytesPP + 2];
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 1] = ptrBuffer[(c + r * header.width) * bytesPP + 1];
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 2] = ptrBuffer[(c + r * header.width) * bytesPP + 0];
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 3] = ptrBuffer[(c + r * header.width) * bytesPP + 3];
				}
				else if (bytesPP == 3)
				{
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 0] = ptrBuffer[(c + r * header.width) * bytesPP + 2];
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 1] = ptrBuffer[(c + r * header.width) * bytesPP + 1];
					ptrPixels[(c + (header.height - r - 1) * header.width) * bytesPP + 2] = ptrBuffer[(c + r * header.width) * bytesPP + 0];
				}
			}
		}

		free(ptrBuffer);

	}
	else if (header.type == 10)	// run length encoded, non color mapped RGB
	{
		// find the start of the data
		fseek(ptrFile, header.map_start + header.map_length * bytesPP + 18, SEEK_SET);

		// start at the top left
		// work through the bitmap
		c = 0; r = header.height - 1;

		while (r >= 0)
		{
			// read in the packet header
			fread(&packetHeader, sizeof(packetHeader), 1, ptrFile);

			// find the number of reps
			n = packetHeader & 0x7F;

			*((int*)pixel) = 0;
			if (n != packetHeader) // if bit = 1, the next pixel repeated N times
				fread(&pixel, bytesPP, 1, ptrFile);

			// loop n times
			for (i = 0; i < n + 1; i++)
			{
				// if bit = 0, N individual pixels	
				if (n == packetHeader) 
					fread(&pixel, bytesPP, 1, ptrFile);

				if (bytesPP == 4)
				{
					ptrPixels[(c + r * header.width) * bytesPP + 0] = pixel[2];
					ptrPixels[(c + r * header.width) * bytesPP + 1] = pixel[1];
					ptrPixels[(c + r * header.width) * bytesPP + 2] = pixel[0];
					ptrPixels[(c + r * header.width) * bytesPP + 3] = pixel[3];
				}
				else if (bytesPP == 3)
				{
					ptrPixels[(c + r * header.width) * bytesPP + 0] = pixel[2];
					ptrPixels[(c + r * header.width) * bytesPP + 1] = pixel[1];
					ptrPixels[(c + r * header.width) * bytesPP + 2] = pixel[0];
				}
				// move to the next pixel
				c += 1;
				if (c >= header.width)
				{
					c = 0;
					r -= 1;
				}
			}
		}
	}
	// close the file
	fclose(ptrFile);

	// create an OpenGL texture
	glGenTextures(1, &textureHandle);

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, header.width, header.height, GL_RGB, GL_UNSIGNED_BYTE, ptrPixels);

	// delete the pixel data
	free(ptrPixels);
}

GLuint Texture::getTextureHandle(void)
{
	return textureHandle;
}
