#include "mesh.hpp"
#include <GLFW/glfw3.h>


std::unordered_map<VertexFormat, std::vector<GLuint>> ff{
	{VertexFormat::Pos,{3,3}},
	{VertexFormat::Pos_N,{3,3,6}} ,
	{VertexFormat::Pos_N_UV,{3,3,2,8}}
};

//这个是按OpenGL教程中提供 glfloat数组格式 顶点和索引的处理函数
Mesh::Mesh(GLfloat vertices[], GLuint v_size, 
			GLuint indices[], GLuint i_size, VertexFormat vertexFormat)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
	m_vertexSize = v_size / ff[vertexFormat].back() / sizeof(GLfloat);

	if (indices) {
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
		m_useIndice = true;
		m_indiceSize = i_size / sizeof(GLuint);
	}

	int offset = 0;
	for (int i = 0; i < ff[vertexFormat].size() - 1; i++)
	{
		glVertexAttribPointer(i, ff[vertexFormat][i], GL_FLOAT, GL_FALSE, 
			ff[vertexFormat].back() * (sizeof(GLfloat)), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(i);
		offset += ff[vertexFormat][i];
	}

	//cleanup
	glBindVertexArray(0);
	glDeleteBuffers(1, &m_VBO);
	if (indices) { glDeleteBuffers(1, &m_EBO); }
}


void Mesh::draw(Shader &shader) {
	shader.active();
	glBindVertexArray(m_VAO);
	if (m_useIndice) { glDrawElements(GL_TRIANGLES, m_indiceSize, GL_UNSIGNED_INT, 0); }
				else { glDrawArrays(GL_TRIANGLES, 0, m_vertexSize); }
	glBindVertexArray(0);
}