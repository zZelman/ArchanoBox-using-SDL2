#pragma once

#include "stdafx.h"

// * This class serves to load all image formats from the given file path in the method parameters
//		The loaded file is given by the return
// * In the case of SDL2_image.lib, this class serves as a wrapper
// * The constructor/destructor do nothing
// * Assertions are embedded within the methods if DEBUG (default preprocessor debug deff)
class CImageLoader_SDL
{
public:
	CImageLoader_SDL(void);
	~CImageLoader_SDL(void);

	// enables loading using SDL2_image.lib
	void initLoading(int flags);

	// concatenates the file path and the name in to a std::string
	std::string catPathAndName(std::string filePath, std::string imageName);

	// Loads a BMP image into a SDL Surface
	SDL_Surface* loadSurface_BMP(const char* pFilePath);

	// Loads a BMP image into a SDL Surface and then optimizes it for the specified settings
	SDL_Surface* loadSurface_BMP_Converted(const char* pFilePath,
	                                       SDL_PixelFormat* pPixlFormat,
	                                       Uint32 flags);

	// Loads an image into a SDL Surface
	// Uses SDL2_image.lib
	SDL_Surface* loadSurface_IMGlib(const char* pFilePath);

	// Loads an image into a SDL Surface and then optimizes it for the specified settings
	// Uses SDL2_image.lib
	SDL_Surface* loadSurface_IMGlib_Converted(const char* pFilePath,
	        SDL_PixelFormat* pPixlFormat,
	        Uint32 flags);
};

