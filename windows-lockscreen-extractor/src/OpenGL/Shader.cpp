#include "Shader.h"

#include <iostream>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	std::unordered_map<GLenum, std::string> src;
	src[GL_VERTEX_SHADER] = vertexSrc;
	src[GL_FRAGMENT_SHADER] = fragmentSrc;
	Compile(src);
}

void Shader::Compile(const std::unordered_map<GLenum, std::string>& src)
{
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	GLuint program = glCreateProgram();

	GLenum shaderIDs[2] = { 0 };
	size_t counter = 0;
	for (auto& v : src)
	{
		GLenum type = v.first;
		const std::string& shaderSrc = v.second;

		// Create an empty shader handle
		GLuint shaderID = glCreateShader(type);

		// Send the shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)shaderSrc.c_str();
		glShaderSource(shaderID, 1, &source, 0);

		// Compile the shader
		glCompileShader(shaderID);

		GLint isCompiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shaderID);

			// Use the infoLog as you see fit.
			std::cout << infoLog.data() << std::endl;

			// In this simple program, we'll just leave
			return;
		}

		glAttachShader(program, shaderID);
		shaderIDs[counter++] = shaderID;
	}

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);

		// Don't leak shaders either.
		for (auto id: shaderIDs)
			glDeleteShader(id);

		// Use the infoLog as you see fit.
		std::cout << infoLog.data() << std::endl;

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	for (auto id : shaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}

	m_RendererID = program;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}
