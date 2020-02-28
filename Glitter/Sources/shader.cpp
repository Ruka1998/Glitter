#include "shader.hpp"
#include <fstream>

Shader& Shader::attach(std::string filename) {
	std::string path = PROJECT_SOURCE_DIR "/Glitter/Shaders/";
	std::ifstream fd(path + filename);
	std::string sourceStr(std::istreambuf_iterator<GLchar>(fd), 
						 (std::istreambuf_iterator<GLchar>()));
	GLuint shader = create(filename);
	const GLchar* source = sourceStr.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &m_status);
	if (!m_status) {
		GLchar infoLog[256];
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << filename << " compile failed :\n" << infoLog << std::endl;
	}
	glAttachShader(m_program, shader);
	glDeleteShader(shader);
	return *this;
}
void Shader::link() {
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &m_status);
	if (!m_status) {
		GLchar infoLog[512];
		glGetProgramInfoLog(m_program, sizeof(infoLog), NULL, infoLog);
		std::cout << "program link failed :\n" << infoLog << std::endl;
	}
}

GLuint Shader::create(std::string filename) {
	GLuint shader;
	std::string ext = filename.substr(filename.find_last_of('.') + 1);

		 if (ext == "vert") { shader = glCreateShader(GL_VERTEX_SHADER); }
	else if (ext == "frag") { shader = glCreateShader(GL_FRAGMENT_SHADER); }

	return shader;
}

void Shader::bind(GLint loc, GLfloat value) {
	glUniform1f(loc, value);
}

void Shader::bind(GLint loc, glm::mat4& const matrix) {
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}