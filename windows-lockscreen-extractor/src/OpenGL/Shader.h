#pragma once

#include <glad/glad.h>

#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader() = default;

	void Bind() const;
	void Unbind() const;
private:
	void Compile(const std::unordered_map<GLenum, std::string>& src);
private:
	GLuint m_RendererID;
};
