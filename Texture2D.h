#pragma once

using Texture2DID = unsigned int;

class Texture2D
{
public:

	Texture2D(const char* imagePath, GLenum imageDataFormat);
	~Texture2D();

	void Bind();
	void Unbind();
	void Activate(GLenum textureUnit);

	void SetWrapMode(GLenum wrapS, GLenum wrapT);
	void SetFilterMode(GLenum minFilter, GLenum magFilter);

private:
	Texture2DID m_textureId;
};
