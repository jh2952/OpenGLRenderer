#pragma once

using ElementBufferID = unsigned int;

class ElementBuffer
{
public:
	ElementBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;

private:
	ElementBufferID m_bufferID;
};