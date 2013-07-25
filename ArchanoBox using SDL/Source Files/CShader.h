#pragma once

#include "stdafx.h"

// A temporary class to test shader tutorials
class CShader
{
public:
	CShader(void);
	~CShader(void);

	const char* getVS()
	{
		return m_pVertexShader;
	}

	const char* getFS()
	{
		return m_pFragmentShader;
	}

	GLuint getVBO()
	{
		return m_VertexBufferObject;
	}

	GLuint getIBO()
	{
		return m_IndexBufferObject;
	}

	// * returns the value of the shader variable
	// * 'name' is the exact name from the shader of the variable
	GLuint getShaderVar(const std::string& name);

	// [TEMPORARY LOCATION]
	// just checking the functionality of the hash-map
	GLuint m_shaderVar_gWVP;
	GLuint m_shaderVar_gSampler;

private:
	const char* m_pVertexShader;
	const char* m_pFragmentShader;
	GLuint m_VertexBufferObject;
	GLuint m_IndexBufferObject;

	typedef std::unordered_map<std::string, GLuint> shaderMap;
	shaderMap m_shaders; // hash map of all shaders

	void createVertexBuffer(void);
	void createIndexBuffer(void);
	void loadShaderFile(std::string filePath, std::string& fileContentsOut);
	void compileShaders(void);
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
};