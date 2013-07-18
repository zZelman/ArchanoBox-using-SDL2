#include "stdafx.h"

#include "CImageLoader_SDL.h"


CImageLoader_SDL::CImageLoader_SDL(void) {}
CImageLoader_SDL::~CImageLoader_SDL(void) {}

// enables loading using SDL2_image.lib
void CImageLoader_SDL::initLoading(int flags)
{
	int isInitSuccess = IMG_Init(flags);

#ifdef DEBUG
	assert(isInitSuccess & flags);
#endif // DEBUG
}

// concatenates the file path and the name in to a std::string
std::string CImageLoader_SDL::catPathAndName(std::string filePath, std::string imageName)
{
	filePath.operator += (imageName);
	return filePath;
}

// Loads a BMP image into a SDL Surface
SDL_Surface* CImageLoader_SDL::loadSurface_BMP(const char* pFilePath)
{
	SDL_Surface* pBMPImageReturn = NULL;
	pBMPImageReturn = SDL_LoadBMP(pFilePath);

#ifdef DEBUG
	assert(pBMPImageReturn);
#endif // DEBUG

	return pBMPImageReturn;
}

// Loads a BMP image into a SDL Surface and then optimizes it for the specified settings
SDL_Surface* CImageLoader_SDL::loadSurface_BMP_Converted(const char* pFilePath,
        SDL_PixelFormat* pPixlFormat,
        Uint32 flags)
{
	SDL_Surface* pBMPImage = this->loadSurface_BMP(pFilePath);

	SDL_Surface* pOptimizedBMPImage = SDL_ConvertSurface(pBMPImage, pPixlFormat, flags);

#ifdef DEBUG
	assert(pOptimizedBMPImage);
#endif // DEBUG

	// do not need old surface
	SDL_FreeSurface(pBMPImage);

	return pOptimizedBMPImage;
}

// Loads a PNG image into a SDL Surface
// Uses SDL2_image.lib
SDL_Surface* CImageLoader_SDL::loadSurface_IMGlib(const char* pFilePath)
{
	SDL_Surface* pImageReturn = NULL;
	pImageReturn = IMG_Load(pFilePath);

#ifdef DEBUG
	assert(pImageReturn);
#endif // DEBUG

	return pImageReturn;
}

// Loads a PNG image into a SDL Surface and then optimizes it for the specified settings
// Uses SDL2_image.lib
SDL_Surface* CImageLoader_SDL::loadSurface_IMGlib_Converted(const char* pFilePath,
        SDL_PixelFormat* pPixlFormat,
        Uint32 flags)
{
	SDL_Surface* pImage = this->loadSurface_IMGlib(pFilePath);

	SDL_Surface* pOptimizedImage = SDL_ConvertSurface(pImage, pPixlFormat, flags);

#ifdef DEBUG
	assert(pOptimizedImage);
#endif // DEBUG

	// do not need old surface
	SDL_FreeSurface(pImage);

	return pOptimizedImage;
}