#include "AssetManager.h"



std::unique_ptr<ShaderProgram> AssetManager::createShaderProgram(const std::string & vspath, const std::string & fspath)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		vShaderFile.open(vspath);
		if (!vShaderFile.is_open())
			throw std::invalid_argument("Vertex shader file not found.");
		fShaderFile.open(fspath);
		if (!fShaderFile.is_open())
			throw std::invalid_argument("Fragment shader file not found.");
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const std::exception& ex)
	{
		std::string errmsg;
		errmsg.append("Error: Shader files couldn't be read:\n");
		errmsg.append(ex.what());
		throw std::logic_error(errmsg.c_str());
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	GLint success;
	GLchar infoLog[512];
	vertexShader = glCreateShader(GL_VERTEX_SHADER); GLERR
	glShaderSource(vertexShader, 1, &vShaderCode, NULL); GLERR
	glCompileShader(vertexShader); GLERR
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); GLERR
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); GLERR
		std::string errmsg;
		errmsg.append("Compiler error in vertex shader:\n");
		errmsg.append(infoLog);
		glDeleteShader(vertexShader); GLERR
		throw std::logic_error(errmsg.c_str());
	}
	else {
		std::cout << "Vertex shader compiled successfully!"<< std::endl;
	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); GLERR
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL); GLERR
	glCompileShader(fragmentShader); GLERR
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); GLERR
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); GLERR
		std::string errmsg;
		errmsg.append("Compiler error in fragment shader:\n");
		errmsg.append(infoLog);
		glDeleteShader(vertexShader); GLERR
		glDeleteShader(fragmentShader); GLERR
		throw std::logic_error(errmsg.c_str());
	}
	else {
		std::cout << "Fragment shader compiled successfully!" << std::endl;
	}
	program = glCreateProgram(); GLERR
	glAttachShader(program, vertexShader); GLERR
	glAttachShader(program, fragmentShader); GLERR
	glLinkProgram(program); GLERR
	glGetProgramiv(program, GL_LINK_STATUS, &success); GLERR
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog); GLERR
		std::string errmsg;
		errmsg.append("Linker error in program:\n");
		errmsg.append(infoLog);
		glDetachShader(program, vertexShader); GLERR
		glDetachShader(program, fragmentShader); GLERR
		glDeleteShader(vertexShader); GLERR
		glDeleteShader(fragmentShader); GLERR
		throw std::logic_error(errmsg.c_str());
	}
	glDetachShader(program, vertexShader); GLERR
	glDetachShader(program, fragmentShader); GLERR
	glDeleteShader(vertexShader); GLERR
	glDeleteShader(fragmentShader); GLERR
	return std::unique_ptr<ShaderProgram>(new ShaderProgram(program));
}


ShaderProgram * AssetManager::getShaderProgram(const std::string & name)
{
	auto it = m_shaders.find(name);
	if (it != m_shaders.end())
		return it->second.get();
	return nullptr;
}


void AssetManager::addShaderProgram(const std::string & name, std::unique_ptr<ShaderProgram>&& shader)
{
	m_shaders.insert(std::make_pair(name, std::move(shader)));
}


bool AssetManager::removeShaderProgram(const std::string & name)
{
	return m_shaders.erase(name);
}

