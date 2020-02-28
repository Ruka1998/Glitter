#pragma once

#include "glitter.hpp"
#include "shader.hpp"

#include <unordered_map>

struct Vertex_pos
{
	glm::vec3 position;
};
struct Vertex_pos_n
{
	glm::vec3 position;
	glm::vec3 normal;
};
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

enum class VertexFormat
{
	Pos, Pos_N, Pos_N_UV
};

class Mesh
{
public:
	Mesh() { glGenVertexArrays(1, &m_VAO); }
	~Mesh() { glDeleteVertexArrays(1, &m_VAO); }
	Mesh(GLfloat vertices[], GLuint v_size, GLuint indices[], GLuint i_size, VertexFormat vertexFormat);
	void draw(Shader &shader);
private:
	GLuint m_VAO, m_VBO, m_EBO;
	GLuint m_vertexSize, m_indiceSize;
	GLboolean m_useIndice = false;
};