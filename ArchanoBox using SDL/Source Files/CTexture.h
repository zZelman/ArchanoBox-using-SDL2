#pragma once

#include "stdafx.h"

class CTexture
{
public:
	CTexture(GLenum textureTarget, const std::string& fileName);

	// loads texture
	void load();

	// bind the specific texture loaded to OpenGL texture rendering
	// this texture will remain bound to this texture unit until the next call to 
	//		Texture::Bind() is made with the same texture unit
	void bind(GLenum textureUnit);


private:
	std::string m_textureFilePath;
	std::string m_fileName;

	GLenum m_textureTarget;
	GLuint m_textureObject;

	Magick::Image* m_pImage;
	Magick::Blob m_BLOB; // binary large object
};