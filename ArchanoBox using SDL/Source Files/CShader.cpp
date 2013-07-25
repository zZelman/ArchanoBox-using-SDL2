#include "stdafx.h"

#include "CShader.h"
#include "CTransformationPipeline.h"


void CShader::createVertexBuffer(void)
{
	// contains both the world coords and the texture coords for the triangle
	//SVertex vertices[4] = { 
	//	SVertex(SVector3f(-1.0f, -1.0f, 0.5773f),	SVector2f(0.0f, 0.0f)),
	//	SVertex(SVector3f(0.0f, -1.0f, -1.15475f),	SVector2f(0.5f, 0.0f)),
	//	SVertex(SVector3f(1.0f, -1.0f, 0.5773f),	SVector2f(1.0f, 0.0f)),
	//	SVertex(SVector3f(0.0f, 1.0f, 0.0f),		SVector2f(0.5f, 1.0f)) 
	//};

	SVector3f vertices[4];
	vertices[0] = SVector3f(-1.0f, -1.0f, 0.5773f);
	vertices[1] = SVector3f(0.0f, -1.0f, -1.15475f);
	vertices[2] = SVector3f(1.0f, -1.0f, 0.5773f);
	vertices[3] = SVector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &m_VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}


void CShader::createIndexBuffer(void)
{
	unsigned int indices[] = {	0, 3, 1,
								1, 3, 2,
								2, 3, 0,
								0, 2, 1
							 };

	glGenBuffers(1, &m_IndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


void CShader::loadShaderFile(std::string filePath, std::string& fileContentsOut)
{
	std::ifstream file;
	file.open(filePath.c_str());
#ifdef DEBUG
	assert(file);
#endif // DEBUG

	std::stringstream stream;

	stream << file.rdbuf();

	file.close();

	fileContentsOut = stream.str();
}


void CShader::compileShaders(void)
{
	GLuint shaderProgram = glCreateProgram();
#ifdef DEBUG
	assert(shaderProgram != 0);
#endif // DEBUG

	addShader(shaderProgram, m_pVertexShader, GL_VERTEX_SHADER);
	addShader(shaderProgram, m_pFragmentShader, GL_FRAGMENT_SHADER);

	GLint success = 0;

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
#ifdef DEBUG
	assert(success != 0);
#endif // DEBUG

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
#ifdef DEBUG
	assert(success);
#endif // DEBUG

	glUseProgram(shaderProgram);

	GLuint shaderVar_gWVP = glGetUniformLocation(shaderProgram, "gWVP");
#ifdef DEBUG
	assert(shaderVar_gWVP != 0xFFFFFFFF);
#endif // DEBUG
	m_shaders.insert(shaderMap::value_type("gWVP", shaderVar_gWVP)); // add to hash-map
	m_shaderVar_gWVP = shaderVar_gWVP;


//	GLuint shaderVar_gSampler = glGetUniformLocation(shaderProgram, "gSampler");
//#ifdef DEBUG
//	assert(shaderVar_gWVP != 0xFFFFFFFF);
//#endif // DEBUG
//	m_shaders.insert(shaderMap::value_type("gSampler", shaderVar_gSampler)); // add to hash-map
//	m_shaderVar_gSampler = m_shaderVar_gSampler;
//	//set the index of the texture unit we are going to use into the sampler uniform variable in the shader
//	glUniform1i(m_shaderVar_gSampler, 0);
}


void CShader::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
#ifdef DEBUG
	assert(shaderObj != 0);
#endif // DEBUG

	const GLchar* p[1];
	p[0] = pShaderText;

	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);

	glShaderSource(shaderObj, 1, p, Lengths);
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
#ifdef DEBUG
	assert(success);
#endif // DEBUG

	glAttachShader(shaderProgram, shaderObj);
}


CShader::CShader(void)
{
	this->createVertexBuffer();
	this->createIndexBuffer();

	std::string vs_source;
	this->loadShaderFile("Resource Files/Shaders/VertexShader.vert", vs_source);
	this->m_pVertexShader = vs_source.c_str();

	std::string fs_source;
	this->loadShaderFile("Resource Files/Shaders/FragmentShader.frag", fs_source);
	this->m_pFragmentShader = fs_source.c_str();

	this->compileShaders();
}


CShader::~CShader(void)
{

}


GLuint CShader::getShaderVar(const std::string& name)
{
	shaderMap::const_iterator itr = m_shaders.find(name);

#ifdef DEBUG
	assert(itr != m_shaders.end());
#endif // DEBUG

	return itr->second;
}