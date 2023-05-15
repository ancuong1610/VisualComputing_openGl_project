#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_
#include <libheaders.h>

struct VertexAttribute
{
	GLint n;
	GLenum type;
	GLsizei stride;
	GLintptr offset;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;
};

typedef GLuint Index;

#endif