#pragma once

// Not completed!!

class CTestRendering
{
private:
	char* m_pVS;
	char* m_pFS;
	GLuint m_VBO;
	GLuint m_WorldLocation;

public:

private:
	void createVertexBuffer(void);
	void compileShaders(void);
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

public:
	CTestRendering(void);
	~CTestRendering(void);

	void render(void);
};

