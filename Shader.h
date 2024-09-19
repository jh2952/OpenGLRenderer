#pragma once

using ShaderID = unsigned int;

class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	ShaderID GetID() const { return m_shaderId; }

	void Use();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMatrix2x2f(const std::string& name, glm::mat2 mtx) const;
	void SetMatrix3x3f(const std::string& name, glm::mat3 mtx) const;
	void SetMatrix4x4f(const std::string& name, glm::mat4 mtx) const;

private:
	ShaderID m_shaderId;
};