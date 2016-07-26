/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

#include "texture.h"

using namespace System::Windows::Forms;



bool icompare_predicate(unsigned char a, unsigned char b)
{
	return tolower(a) == tolower(b);
}

bool icompare(std::string const& a, std::string const& b)
{
	if (a.length() == b.length()) {
		return std::equal(b.begin(), b.end(), a.begin(), icompare_predicate);
	}
	else {
		return false;
	}
}


Texture::Texture(char* imagePath)
{
	std::string filePath = imagePath;
	textureFileExt = filePath.substr( filePath.rfind(".") + 1 );
	int tfeSize = textureFileExt.length();

	if (tfeSize == 0)
	{
		MessageBox::Show("Unsupported texture file");
		exit(1);
	}
	
	// Try open the texture file
	if (((ptrFile = fopen(imagePath, "rb")) == NULL)) {
		MessageBox::Show("Unable to open requested texture file");
		exit(1);
	}

	if (icompare(textureFileExt, tgaAllowed))
	{
		LoadTGATexture(ptrFile);
	}
	else if (icompare(textureFileExt, bmpAllowed))
	{
		LoadBMPTexture(ptrFile);
	}
	else
	{
		MessageBox::Show("Unsupported texture file");
		exit(1);
	}

}

GLuint Texture::getTextureHandle(void)
{
	return textureHandle;
}

void Texture::LoadTGATexture(FILE *ptrTextureFile)
{
	TGAHeader header;	// structure for the header info

	// column counter, row counter, i loop counters, and bytes per pixel
	int c, r, i, j, bytesPP = 4;
	char n, packetHeader;
	char pixel[4];

	// read the header
	fread(&header, 18, 1, ptrTextureFile);

	// bytes per pixel
	bytesPP = header.bpp / 8;

	ptrTexturePixels = (char*)malloc(bytesPP * header.width * header.height);

	// Decode texture
	// header type 2 is uncompressed RGB data without a color map / palette
	if (header.type == 2)
	{
		// seek to the start of the data
		fseek(ptrTextureFile, header.map_start + header.map_length * bytesPP + 18, SEEK_SET);

		// read the pixel data into a buffer
		ptrTextureBuffer = (char*)malloc(bytesPP * header.width * header.height);
		fread(ptrTextureBuffer, bytesPP, header.width * header.height, ptrTextureFile);

		// plot the pixel data into pixels buffer
		for (c = 0; c < header.width; c++)	// count up columns
		{
			for (r = 0; r < header.height; r++)	// rows
			{
				if (bytesPP == 4)
				{
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 0] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 2];
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 1] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 1];
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 2] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 0];
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 3] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 3];
				}
				else if (bytesPP == 3)
				{
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 0] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 2];
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 1] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 1];
					ptrTexturePixels[(c + (header.height - r - 1) * header.width) * bytesPP + 2] = ptrTextureBuffer[(c + r * header.width) * bytesPP + 0];
				}
			}
		}

		free(ptrTextureBuffer);

	}
	else if (header.type == 10)	// run length encoded, non color mapped RGB
	{
		// find the start of the data
		fseek(ptrTextureFile, header.map_start + header.map_length * bytesPP + 18, SEEK_SET);

		// start at the top left
		// work through the bitmap
		c = 0; r = header.height - 1;

		while (r >= 0)
		{
			// read in the packet header
			fread(&packetHeader, sizeof(packetHeader), 1, ptrTextureFile);

			// find the number of reps
			n = packetHeader & 0x7F;

			*((int*)pixel) = 0;
			if (n != packetHeader) // if bit = 1, the next pixel repeated N times
				fread(&pixel, bytesPP, 1, ptrTextureFile);

			// loop n times
			for (i = 0; i < n + 1; i++)
			{
				// if bit = 0, N individual pixels	
				if (n == packetHeader)
					fread(&pixel, bytesPP, 1, ptrTextureFile);

				if (bytesPP == 4)
				{
					ptrTexturePixels[(c + r * header.width) * bytesPP + 0] = pixel[2];
					ptrTexturePixels[(c + r * header.width) * bytesPP + 1] = pixel[1];
					ptrTexturePixels[(c + r * header.width) * bytesPP + 2] = pixel[0];
					ptrTexturePixels[(c + r * header.width) * bytesPP + 3] = pixel[3];
				}
				else if (bytesPP == 3)
				{
					ptrTexturePixels[(c + r * header.width) * bytesPP + 0] = pixel[2];
					ptrTexturePixels[(c + r * header.width) * bytesPP + 1] = pixel[1];
					ptrTexturePixels[(c + r * header.width) * bytesPP + 2] = pixel[0];
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
	fclose(ptrTextureFile);

	// create an OpenGL texture
	glGenTextures(1, &textureHandle);

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, header.width, header.height, GL_RGB, GL_UNSIGNED_BYTE, ptrTexturePixels);

	// delete the pixel data
	free(ptrTexturePixels);
}

void Texture::LoadBMPTexture(FILE *ptrTextureFile)
{
	int width, height, c, whm;

	width = 1024;
	height = 512;
	c = 3;
	whm = width * height;

	ptrTexturePixels = (char *)malloc(whm * c);

	fread(ptrTexturePixels, whm * c, 1, ptrTextureFile);
	fclose(ptrTextureFile);

	for (int i = 0; i < whm; ++i)
	{
		int index = i * c;
		char B, R;
		B = ptrTexturePixels[index];
		R = ptrTexturePixels[index + 2];

		ptrTexturePixels[index] = R;
		ptrTexturePixels[index + 2] = B;

	}

	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, c, width, height, GL_RGB, GL_UNSIGNED_BYTE, ptrTexturePixels);

	free(ptrTexturePixels);

}
