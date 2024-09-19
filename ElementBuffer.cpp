#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(const void* data, size_t size, GLenum usage)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
