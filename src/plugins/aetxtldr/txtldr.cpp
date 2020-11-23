/*
 *  AE Engine
 *
 *  Copyright (C) 2003 Riku "Rakkis" Nurminen
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <aedefs.h>
#include <aegfx/texture.h>
#include <aeplugin/plugin.h>
#include <aereg/registry.h>
#include <aetxtldr/txtldr.h>
#include <aeutil/util.h>

aeTextureLoader::aeTextureLoader(aeRegistry *aeReg)
{
	AECF_CNAME("aeTextureLoader")
	myID = AE_PLUGIN_aeTextureLoader;

	aereg = aeReg;
}

aeTextureLoader::~aeTextureLoader()
{
}

aeTextureType aeTextureLoader::GetImageType(char *image)
{
	char *ptr;
	if((ptr = strrchr(image, '.')) != NULL) {
		if(strstr(ptr + 1, "bmp"))
			return AE_TEXTURE_BMP;
		if(strstr(ptr + 1, "pcx"))
			return AE_TEXTURE_PCX;
		if(strstr(ptr + 1, "tga"))
			return AE_TEXTURE_TGA;
	}
	return AE_TEXTURE_UNKNOWN;
}

aeTexture *aeTextureLoader::LoadTexture(char *name, char *image)
{
	aeTexture *texture = NULL;

	switch(GetImageType(image)) {
	case AE_TEXTURE_BMP:
		texture = LoadBMP(name, image);
		break;
	case AE_TEXTURE_PCX:
		texture = LoadPCX(name, image);
		break;
	case AE_TEXTURE_TGA:
		texture = LoadTGA(name, image);
		break;
	case AE_TEXTURE_UNKNOWN:
		break;
	default:
		break;
	}

	if(texture != NULL)
		aereg->PushTextureToPool(texture);

	return texture;
}

aeTexture *aeTextureLoader::LoadBMP(char *tstring, char *image)
{
	aeTexture *bmptex;
	FILE *fd;
	bmpFileHeader bfheader;
	bmpHeader bmpheader;
	unsigned char *bmpdata = NULL;
	int index = 0;
	unsigned char colorSwap;
	int bmpsize, colorMode;
	unsigned char *tempbuf;

	fd = fopen(image, "rb");
	if(fd == NULL) {
		return NULL;
	}

	// Fill in the bmpFileHeader struct. We do it the hard way instead of
	// fread(&bfheader, sizeof(bmpFileHeader), 1, fd) because of struct member aligment
	tempbuf = new unsigned char[14];
	fread(tempbuf, 14, 1, fd);
	memcpy(&bfheader.bfType, tempbuf, sizeof(bfheader.bfType));
	memcpy(&bfheader.bfSize, tempbuf + 2, sizeof(bfheader.bfSize));
	memcpy(&bfheader.bfReserved1, tempbuf + 6, sizeof(bfheader.bfReserved1));
	memcpy(&bfheader.bfReserved2, tempbuf + 8, sizeof(bfheader.bfReserved2));
	memcpy(&bfheader.bfOffBits, tempbuf + 10, sizeof(bfheader.bfOffBits));
	delete tempbuf;

	// Verify that this is a valid BMP file
	if(bfheader.bfType != 0x4D42) {
		fclose(fd);
		aeUtil::Report("ae.textureloader.LoadBMP", "Error loading %s: not a valid BMP file (bmp id: %x)\n", image, bfheader.bfType);
		return NULL;
	}

	// Read the bmp info header
	fread(&bmpheader, sizeof(bmpHeader), 1, fd);

	// Check that this is a 24-bit image
	if(bmpheader.biBitCount == 24) {
		// Calculate bytes per pixel and the size of image data
		colorMode = bmpheader.biBitCount / 8;
		bmpsize = bmpheader.biWidth * bmpheader.biHeight * colorMode;

		// Malloc memory for image data
		bmpdata = new unsigned char[sizeof(unsigned char) * bmpsize];

		// Seek to start of bmp data
		fseek(fd, bfheader.bfOffBits, SEEK_SET);

		// Read the bmp image data
		fread(bmpdata, sizeof(unsigned char), bmpsize, fd);

		// Swap the RGB values since BMPs are stored in BGR
		for(index = 0; index < bmpsize; index += 3){
			colorSwap = bmpdata[index];
			bmpdata[index] = bmpdata[index + 2];
			bmpdata[index + 2] = colorSwap;
		}
	} else {
		fclose(fd);
		aeUtil::Report("ae.textureloader.LoadBMP", "%s has bad or unsupported pixel format\n", image);
		return NULL;
	}

	fclose(fd);
	bmptex = new aeTexture(tstring, bmpdata, bmpheader.biWidth, bmpheader.biHeight, bmpheader.biBitCount);
	return bmptex;
}

aeTexture *aeTextureLoader::LoadTGA(char *tstring, char *image)
{
	aeTexture *tgatex;
	FILE *fd;
	tgaHeader tgaheader;
	unsigned char *tgadata = NULL;
	unsigned int index, colorMode;
	unsigned char colorSwap;
	unsigned long int tgasize;
	unsigned char *tempbuf;

	fd = fopen(image, "rb");
	if(fd == NULL) {
		return NULL;
	}

	// Fill in the tgaheader struct. We do it the hard way like above..
	tempbuf = new unsigned char[18];
	fread(tempbuf, 18, 1, fd);
	memcpy(&tgaheader.imageIDLength, tempbuf, sizeof(tgaheader.imageIDLength));
	memcpy(&tgaheader.colorMapType, tempbuf + 1, sizeof(tgaheader.colorMapType));
	memcpy(&tgaheader.imageTypeCode, tempbuf + 2, sizeof(tgaheader.imageTypeCode));
	memcpy(&tgaheader.colorMapOrigin, tempbuf + 3, sizeof(tgaheader.colorMapOrigin));
	memcpy(&tgaheader.colorMapLength, tempbuf + 5, sizeof(tgaheader.colorMapLength));
	memcpy(&tgaheader.colorMapEntrySize, tempbuf + 7, sizeof(tgaheader.colorMapEntrySize));
	memcpy(&tgaheader.imageXOrigin, tempbuf + 9, sizeof(tgaheader.imageXOrigin));
	memcpy(&tgaheader.imageYOrigin, tempbuf + 11, sizeof(tgaheader.imageYOrigin));
	memcpy(&tgaheader.imageWidth, tempbuf + 12, sizeof(tgaheader.imageWidth));
	memcpy(&tgaheader.imageHeight, tempbuf + 14, sizeof(tgaheader.imageHeight));
	memcpy(&tgaheader.bitCount, tempbuf + 16, sizeof(tgaheader.bitCount));
	memcpy(&tgaheader.imageDescriptor, tempbuf + 17, sizeof(tgaheader.imageDescriptor));
	delete tempbuf;

	if((tgaheader.imageTypeCode != TGA_RGB) && (tgaheader.imageTypeCode != TGA_GREY) && (tgaheader.imageTypeCode != TGA_RLERGB) && (tgaheader.imageTypeCode != TGA_RLEGREY)) {
		aeUtil::Report("ae.textureloader.LoadTGA", "%s doesn't look like a TGA image\n", image);
		fclose(fd);
		return NULL;
	}

	// Uncompressed 16-bit & RLE compressed image loading code taken from NeHe. Thanks!

	// Check if this image is regular uncompressed RGB or greyscale image
	if(tgaheader.imageTypeCode == TGA_RGB || tgaheader.imageTypeCode == TGA_GREY) {
		// Check if the image is 24 or 32-bit image
		if(tgaheader.bitCount == 24 || tgaheader.bitCount == 32) {
			colorMode = tgaheader.bitCount / 8;
			tgasize = tgaheader.imageWidth * tgaheader.imageHeight * colorMode;
			tgadata = new unsigned char[sizeof(unsigned char) * tgasize];

			// Read in the TGA image data
			fread(tgadata, sizeof(unsigned char), tgasize, fd);

			// Change BGR to RGB
			for(index = 0; index < tgasize; index += colorMode) {
				colorSwap = tgadata[index];
				tgadata[index] = tgadata[index + 2];
				tgadata[index + 2] = colorSwap;
			}
		} else if(tgaheader.bitCount == 16) {
			unsigned short pixels = 0;
			unsigned char r = 0, g = 0, b = 0;

			// Since we convert 16-bit images to 24 bit, we hardcode the channels to 3.
			// We then calculate the stride and allocate memory for the pixels.
			colorMode = 3;
			tgasize = tgaheader.imageWidth * tgaheader.imageHeight * colorMode;
			tgadata = new unsigned char[sizeof(unsigned char) * tgasize];

			// Load in all the pixel data pixel by pixel
			for(int i = 0; i < tgaheader.imageWidth * tgaheader.imageHeight; i++) {
				// Read in the current pixel
				fread(&pixels, sizeof(unsigned short), 1, fd);

				// To convert a 16-bit pixel into an R, G, B, we need to
				// do some masking and such to isolate each color value.
				// 0x1f = 11111 in binary, so since 5 bits are reserved in
				// each unsigned short for the R, G and B, we bit shift and mask
				// to find each value.  We then bit shift up by 3 to get the full color.
				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;

				// This essentially assigns the color to our array and swaps the
				// B and R values at the same time.
				tgadata[i * 3 + 0] = r;
				tgadata[i * 3 + 1] = g;
				tgadata[i * 3 + 2] = b;
			}
		} else {
			aeUtil::Report("ae.textureloader.LoadTGA", "%s has bad or unsupported pixel format (%d)\n", image, tgaheader.bitCount);
			fclose(fd);
			return NULL;
		}
	} else {
		// It must be a RLE compressed image

		// Create some variables to hold the rleID, current colors read, channels, & stride.
		unsigned char rleID = 0;
		int i = 0;
		int colorsRead = 0;
		colorMode = tgaheader.bitCount / 8;
		tgasize = tgaheader.imageWidth * tgaheader.imageHeight * colorMode;

		// Next we want to allocate the memory for the pixels and create an array,
		// depending on the channel count, to read in for each pixel.
		tgadata = new unsigned char[sizeof(unsigned char) * tgasize];
		unsigned char *pColors = new unsigned char[colorMode];

		// Load in all the pixel data
		while(i < tgaheader.imageWidth * tgaheader.imageHeight) {
			// Read in the current color count + 1
			fread(&rleID, sizeof(unsigned char), 1, fd);

			// Check if we don't have an encoded string of colors
			if(rleID < 128) {
				// Increase the count by 1
				rleID++;

				// Go through and read all the unique colors found
				while(rleID) {
					// Read in the current color
					fread(pColors, sizeof(unsigned char) * colorMode, 1, fd);

					// Store the current pixel in our image array
					tgadata[colorsRead + 0] = pColors[2];
					tgadata[colorsRead + 1] = pColors[1];
					tgadata[colorsRead + 2] = pColors[0];

					// If we have a 4 channel 32-bit image, assign one more for the alpha
					if(tgaheader.bitCount == 32)
						tgadata[colorsRead + 3] = pColors[3];

					// Increase the current pixels read, decrease the amount
					// of pixels left, and increase the starting index for the next pixel.
					i++;
					rleID--;
					colorsRead += colorMode;
				}
			}
			// Else, let's read in a string of the same character
			else {
				// Minus the 128 ID + 1 (127) to get the color count that needs to be read
				rleID -= 127;

				// Read in the current color, which is the same for a while
				fread(pColors, sizeof(unsigned char) * colorMode, 1, fd);

				// Go and read as many pixels as are the same
				while(rleID) {
                   // Assign the current pixel to the current index in our pixel array
                   tgadata[colorsRead + 0] = pColors[2];
                   tgadata[colorsRead + 1] = pColors[1];
                   tgadata[colorsRead + 2] = pColors[0];

                   // If we have a 4 channel 32-bit image, assign one more for the alpha
                   if(tgaheader.bitCount == 32)
                       tgadata[colorsRead + 3] = pColors[3];

                   // Increase the current pixels read, decrease the amount
                   // of pixels left, and increase the starting index for the next pixel.
                   i++;
                   rleID--;
                   colorsRead += colorMode;
				}
			}
		}
		delete pColors;
	}

	fclose(fd);

	tgatex = new aeTexture(tstring, tgadata, tgaheader.imageWidth, tgaheader.imageHeight, tgaheader.bitCount);

	return tgatex;
}

aeTexture *aeTextureLoader::LoadPCX(char *tstring, char *image)
{
	aeTexture *pcxtex;
	int idx = 0;
	int c, i, j;
	int numRepeat;
	FILE *fd;
	int width, scaledWidth;
	int height, scaledHeight;
	int tmpwidth, tmpheight;
	unsigned char *pcxdata;
	unsigned char *unscaledData;
	unsigned char *paletteData;
	pcxHeader pcxhdr;

	memset(&pcxhdr, 0, sizeof(pcxHeader));

	fd = fopen(image, "rb");
	if(fd == NULL)
		return NULL;

	// retrieve first character; should be equal to 10
	c = getc(fd);
	if(c != 10) {
		aeUtil::Report("ae.textureloader.LoadPCX", "%s doesn't look like a PCX image\n", image);
		fclose(fd);
		return NULL;
	}

	// retrieve next character; should be equal to 5
	c = getc(fd);
	if(c != 5) {
		aeUtil::Report("ae.textureloader.LoadPCX", "%s doesn't look like a PCX image\n", image);
		fclose(fd);
		return NULL;
	}

	rewind(fd);

	// read 4 characters of data to skip
	fgetc(fd);
	fgetc(fd);
	fgetc(fd);
	fgetc(fd);

	// retrieve leftmost x value of PCX
	pcxhdr.xMin = fgetc(fd);
	pcxhdr.xMin |= fgetc(fd) << 8;

	// retrieve bottom-most y value of PCX
	pcxhdr.yMin = fgetc(fd);
	pcxhdr.yMin |= fgetc(fd) << 8;

	// retrieve rightmost x value of PCX
	pcxhdr.xMax = fgetc(fd);
	pcxhdr.xMax |= fgetc(fd) << 8;

	// retrieve topmost y value of PCX
	pcxhdr.yMax = fgetc(fd);
	pcxhdr.yMax |= fgetc(fd) << 8;

	// calculate the width and height of the PCX
	width = pcxhdr.xMax - pcxhdr.xMin + 1;
	height = pcxhdr.yMax - pcxhdr.yMin + 1;

	// allocate memory for PCX image data
	pcxdata = new unsigned char[width * height];

	// set file pointer to 128th byte of file, where the PCX image data starts
	fseek(fd, 128, SEEK_SET);

	// decode the pixel data and store
	while(idx < (width * height)) {
		c = getc(fd);
		if(c > 0xbf) {
			numRepeat = 0x3f & c;
			c = getc(fd);

			for(i = 0; i < numRepeat; i++) {
				pcxdata[idx++] = c;
			}
		} else {
			pcxdata[idx++] = c;
		}

		fflush(stdout);
	}

	// allocate memory for the PCX image palette
	paletteData = new unsigned char[768];

	// palette is the last 769 bytes of the PCX file
	fseek(fd, -769, SEEK_END);

	// verify palette; first character should be 12
	c = getc(fd);
	if(c != 12) {
		aeUtil::Report("ae.textureloader.LoadPCX", "%s seems to have a broken palette\n", image);
		fclose(fd);
		return NULL;
	}

	// read and store all of palette
	for(i = 0; i < 768; i++) {
		c = getc(fd);
		paletteData[i] = c;
	}

	// close file and store palette in header
	fclose(fd);
	pcxhdr.palette = paletteData;

	// allocate memory for the unscaled data
	unscaledData = new unsigned char[width * height * 4];

	// store the unscaled data via the palette
	for(j = 0; j < height; j++) {
		for(i = 0; i < width; i++) {
			unscaledData[4 * (j * width + i) + 0] = (unsigned char)paletteData[3 * pcxdata[j * width + i] + 0];
			unscaledData[4 * (j * width + i) + 1] = (unsigned char)paletteData[3 * pcxdata[j * width + i] + 1];
			unscaledData[4 * (j * width + i) + 2] = (unsigned char)paletteData[3 * pcxdata[j * width + i] + 2];
			unscaledData[4 * (j * width + i) + 3] = (unsigned char)255;
		}
	}

	tmpwidth = width;
	tmpheight = height;

	// find width's
	i = 0;
	while(tmpwidth) {
		tmpwidth /= 2;
		i++;
	}
	scaledHeight = (long)pow(2, i - 1);

	// find height's
	i = 0;
	while(tmpheight) {
		tmpheight /= 2;
		i++;
	}
	scaledWidth = (long)pow(2, i - 1);

	// clear the texture data
	if(pcxdata != NULL) {
		delete pcxdata;
		pcxdata = NULL;
	}

	// reallocate memory for the texture data
	pcxdata = new unsigned char[scaledWidth * scaledHeight * 4];
     
	// use the GL utility library to scale the texture to the unscaled dimensions
	gluScaleImage(GL_RGBA, width, height, GL_UNSIGNED_BYTE, unscaledData, scaledWidth, scaledHeight,
				  GL_UNSIGNED_BYTE, pcxdata);

	pcxtex = new aeTexture(tstring, pcxdata, width, height, pcxhdr.bits);

	delete unscaledData;
	delete paletteData;

	// return the pixel image data
	return pcxtex;
}

extern "C" aePlugin *PLUGIN_ENTRY(aeRegistry *aeReg)
{
	aeTextureLoader *txtldrptr = new aeTextureLoader(aeReg);
	return txtldrptr;
}
