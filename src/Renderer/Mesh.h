#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

#include <vector>

struct Vertex
{
	Vertex(const glm::vec3& _position, const glm::vec3& _color) : position(_position), color(_color) {}
	glm::vec3 position;
	glm::vec3 color;
};

class Mesh
{
  public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	void Draw() const;

  private:
	GLuint VAO, VBO, EBO;
	GLsizei indexCount;
};
