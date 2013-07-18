#include "stdafx.h"

CTexture::CTexture(GLenum textureTarget, const std::string& fileName)
{
	m_textureFilePath = "Resource Files/Textures/";
	m_fileName = m_textureFilePath += (fileName);

	m_textureTarget = textureTarget;

	m_pImage = NULL;
}


// loads texture
void CTexture::load()
{
	try
	{
		m_pImage = new Magick::Image(m_fileName);
		m_pImage->write(&m_BLOB, "RGBA");
	}
	catch (Magick::Error& error)
	{
#ifdef DEBUG
		bool textureLoadFailure = false;
		assert(textureLoadFailure);  
#endif // DEBUG
	}

	glGenTextures(1, &m_textureObject);

	// bind the texObj to the type of texture requested (textTarg)
	glBindTexture(m_textureTarget, m_textureObject);

	// target | level of detail (mip-mapping) | color channels | 
	//		width | height | border | format | type | memory address
	// type: ImageMagick only uses one byte for channel
	glTexImage2D(m_textureTarget, 0, GL_RGBA, 
				 m_pImage->columns(), m_pImage->rows(), 
				 0, GL_RGBA, GL_UNSIGNED_BYTE, m_BLOB.data());

	// specify the type of filter to be used for magnification and minification
	//		(linear interpolation [2x2 sampling average])
	glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete m_pImage;
	m_pImage = NULL;
}


// bind the specific texture loaded to OpenGL texture rendering
// this texture will remain bound to this texture unit until the next call to 
//		Texture::Bind() is made with the same texture unit
void CTexture::bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(m_textureTarget, textureUnit);
}