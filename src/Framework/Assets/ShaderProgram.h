#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_
#include <libheaders.h>
#include <glerror.h>


class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(GLuint program);
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;
	ShaderProgram(ShaderProgram&& other);
	ShaderProgram& operator=(ShaderProgram&& other);
	~ShaderProgram();
	void use();
	GLuint prog;
	GLuint currentTu;

	bool isActive()
	{
		if (!prog)
			return false;
		GLint progName = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &progName); GLERR
			if (progName != this->prog)
				return false;
		return true;
	}

	GLuint getFreeTU();
	GLuint getCurrentTU();
	void resetTU(GLuint tu = 0u);

	bool setUniform(const std::string& name, GLfloat value);
	bool setUniform(const std::string& name, const glm::vec2& value);
	bool setUniform(const std::string& name, const glm::vec3& value);
	bool setUniform(const std::string& name, const glm::vec4& value);

	bool setUniform(const std::string& name, GLint value);
	bool setUniform(const std::string& name, const glm::ivec2& value);
	bool setUniform(const std::string& name, const glm::ivec3& value);
	bool setUniform(const std::string& name, const glm::ivec4& value);

	bool setUniform(const std::string& name, GLuint value);
	bool setUniform(const std::string& name, const glm::uvec2& value);
	bool setUniform(const std::string& name, const glm::uvec3& value);
	bool setUniform(const std::string& name, const glm::uvec4& value);

	bool setUniform(const std::string& name, const glm::mat2& value, bool transpose);
	bool setUniform(const std::string& name, const glm::mat3& value, bool transpose);
	bool setUniform(const std::string& name, const glm::mat4& value, bool transpose);

    GLint getUniformLocation(const char* name)
    {
        if (!prog)
            return -1;
        return glGetUniformLocation(this->prog, name); GLERR
    }
};

inline bool ShaderProgram::setUniform(const std::string& name, GLfloat value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform1f(loc, value); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::vec2& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform2fv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::vec3& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform3fv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::vec4& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform4fv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, GLint value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform1i(loc, value); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::ivec2& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform2iv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::ivec3& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform3iv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::ivec4& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform4iv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, GLuint value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform1ui(loc, value); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::uvec2& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform2uiv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::uvec3& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform3uiv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::uvec4& value)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniform4uiv(loc, 1, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::mat2& value, bool transpose)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniformMatrix2fv(loc, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::mat3& value, bool transpose)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniformMatrix3fv(loc, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value)); GLERR
		return true;
}

inline bool ShaderProgram::setUniform(const std::string& name, const glm::mat4& value, bool transpose)
{
	GLint loc = getUniformLocation(name.c_str());
	if (loc == -1)
		return false;
	if (!isActive())
		return false;
	glUniformMatrix4fv(loc, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value)); GLERR
		return true;
}

#endif