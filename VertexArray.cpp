#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

VertexArray::VertexArray(const VertexBuffer& vb)
{
	glGenVertexArrays(1, &m_arrayID);
	glBindVertexArray(m_arrayID);
	vb.Bind();
	Unbind();
}

VertexArray::VertexArray(const VertexBuffer& vb, const ElementBuffer& eb)
{
	glGenVertexArrays(1, &m_arrayID);
	glBindVertexArray(m_arrayID);
	vb.Bind();
	eb.Bind();
	Unbind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_arrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

unsigned int VertexArray::AddVertexAttribute(int count, GLenum type, size_t size, unsigned int offset)
{
	Bind();
	glVertexAttribPointer(m_attribIndex, count, type, GL_FALSE, size, (void*)offset);
	glEnableVertexAttribArray(m_attribIndex);
	Unbind();
	
	return m_attribIndex++;
}
