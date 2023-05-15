#include "ShaderProgram.h"



ShaderProgram::ShaderProgram() :
	prog(0),
	currentTu(0)
{}

ShaderProgram::ShaderProgram(GLuint program) :
	prog(program),
	currentTu(0)
{}

ShaderProgram::ShaderProgram(ShaderProgram && other) :
	prog(other.prog),
	currentTu(0)
{
	other.prog = 0;
}

ShaderProgram & ShaderProgram::operator=(ShaderProgram && other)
{
	if (this == &other)
		return *this;

	if(prog)
		glDeleteProgram(prog);

	prog = other.prog;
	other.prog = 0;
	currentTu = other.currentTu;

	return *this;
}

ShaderProgram::~ShaderProgram()
{
	if(prog)
		glDeleteProgram(prog);
}

void ShaderProgram::use()
{
	resetTU();
	GLint current;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current); GLERR
		if (current != prog && prog != 0)
			glUseProgram(prog); GLERR
}

GLuint ShaderProgram::getFreeTU()
{
	return currentTu++;
}

GLuint ShaderProgram::getCurrentTU()
{
	return currentTu;
}

void ShaderProgram::resetTU(GLuint tu)
{
	currentTu = tu;
}
