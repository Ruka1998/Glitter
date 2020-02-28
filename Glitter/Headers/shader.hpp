#pragma once

#include "glitter.hpp"

class Shader
{
public:
	Shader() { m_program = glCreateProgram(); }
	~Shader() { glDeleteProgram(m_program); }

	void active() { glUseProgram(m_program); }
	GLuint get() { return m_program; }

	Shader& attach(std::string filename);
	void link();

	template <typename T>
	Shader& bind(const std::string& name, T&& value) {
		GLint loc = glGetUniformLocation(m_program, name.c_str());
		if (loc == -1) { std::cout << "Missing Uniform: " << name.c_str() << std::endl; }
		else { bind(loc, std::forward<T>(value)); }
		return *this;
	}

private:
	GLuint create(std::string filename);

	void bind(GLint loc, GLfloat value);
	void bind(GLint loc, glm::mat4& const matrix);

	GLuint m_program;
	GLint m_status;
};