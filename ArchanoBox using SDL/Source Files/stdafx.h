// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
// TODO: reference additional headers your program requires here

// OpenGL Extension Wrangler Library, here because it hates being after OpenGL
// glew32.lib
#include <GL/glew.h>

// SDL generic library
// SDL2.lib and SLD2_main.lib
#include <SDL.h>

#include <SDL_opengl.h>

// SDL image library
// SDL2_image.lib
#include <SDL_image.h>

// glfx_debug.lib and glfx_release.lib respectively
#include <glfx.h>

// texture loading library
#include "ImageMagick/Magick++.h"

// own texture class
#include "CTexture.h"

// Own math lib
#include "Math3D.h"

// timer class based on SDL timer functions
#include "CTimer.h"

// other references
#include <iostream> // cout
#include <assert.h> // assert
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map> // hash-map c++11

#define _USE_MATH_DEFINES
#include <cmath>