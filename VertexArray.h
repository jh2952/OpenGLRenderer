#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"

using VertexArrayID = unsigned int;

class VertexArray
{
public:

	VertexArray(const VertexBuffer& vb);
	VertexArray(const VertexBuffer& vb, const ElementBuffer& eb);
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	unsigned int AddVertexAttribute(int count, GLenum type, size_t size, unsigned int offset);

private:
	unsigned int m_attribIndex{};
	VertexArrayID m_arrayID;
};