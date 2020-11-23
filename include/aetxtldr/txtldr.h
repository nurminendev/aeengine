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

#ifndef __AEPLUGIN_AETXTLDR_TXTLDR_H__
#define __AEPLUGIN_AETXTLDR_TXTLDR_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aegfx/texture.h>
#include <aeplugin/plugin.h>
#include <aereg/registry.h>

/** @defgroup txtldrstructs AE texture loader image structures
 * AE texture loader image structures and definitions.
 * @{
 */

/// TGA types
enum TGATypes {
	/// Uncompressed RGB image.
	TGA_RGB = 2,
	/// Uncompressed greyscale image.
	TGA_GREY = 3,
	/// Run-lenght encoded RGB image.
	TGA_RLERGB = 10,
	/// Run-lenght encoded greyscale image.
	TGA_RLEGREY = 11
};

/// Supported texture types.
enum aeTextureType {
	/// BMP image.
	AE_TEXTURE_BMP,
	/// PCX image.
	AE_TEXTURE_PCX,
	/// TGA image.
	AE_TEXTURE_TGA,
	/// Unknown image.
	AE_TEXTURE_UNKNOWN
};

/** 
 * BITMAPFILEHEADER struct.
 */
typedef struct {
	uint16 bfType;
	uint32 bfSize;
	uint16 bfReserved1;
	uint16 bfReserved2;
	uint32 bfOffBits;
} bmpFileHeader;

/** 
 * BITMAPINFOHEADER struct.
 */
typedef struct {
	uint32 biSize;
	uint32 biWidth;
	uint32 biHeight;
	uint16 biPlanes;
	uint16 biBitCount;
	uint32 biCompression;
	uint32 biSizeImage;
	uint32 biXPelsPerMeter;
	uint32 biYPelsPerMeter;
	uint32 biClrUsed;
	uint32 biClrImportant;
} bmpHeader;

/** 
 * (A partial) PCX file header.
 */
typedef struct {
	unsigned char manufacturer;
	unsigned char version;
	unsigned char encoding;
	unsigned char bits;
	unsigned char xMin;
	unsigned char yMin;
	unsigned char xMax;
	unsigned char yMax;
	unsigned char *palette;
} pcxHeader;

/** 
 * TGA file header.
 */
typedef struct {
	uint8 imageIDLength;
	uint8 colorMapType;
	uint8 imageTypeCode;
	sint8 colorMapOrigin;
	sint16 colorMapLength;
	sint16 colorMapEntrySize;
	sint16 imageXOrigin;
	sint16 imageYOrigin;
	sint16 imageWidth;
	sint16 imageHeight;
	uint8 bitCount;
	uint8 imageDescriptor;
} tgaHeader;

/** @} */

/** 
 * Interface to the texture loader.
 */
class aeTextureLoader: public aePlugin {
	AECF_CNDEF

 private:
	aeRegistry *aereg;

	aeTextureType GetImageType(char *);
	aeTexture *LoadBMP(char *, char *);
	aeTexture *LoadPCX(char *, char *);
	aeTexture *LoadTGA(char *, char *);

 public:
	aeTextureLoader(aeRegistry *aeReg);
	~aeTextureLoader();

	/** 
	 * Load a texture.
	 * 
	 * @param char * Texture name.
	 * @param  char * Path to texture.
	 * 
	 * @return Texture object as aeTexture.
	 */
	virtual aeTexture *LoadTexture(char *, char *);
};

#endif // __AEPLUGIN_AETXTLDR_TXTLDR_H__
