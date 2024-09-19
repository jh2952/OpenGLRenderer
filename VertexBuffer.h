#pragma once

using VertexBufferID = unsigned int;

class VertexBuffer
{
public:

	VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	VertexBufferID m_bufferID;
};