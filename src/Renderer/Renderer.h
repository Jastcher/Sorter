#pragma once

#include "Core/Window.h"

#include "Renderer/Shader.h"

#include <memory>
#include "Core/Sorter.h"

namespace Template
{

class Renderer
{

  public:
	Renderer(std::shared_ptr<Window> window);
	~Renderer();

	void RenderBars(const Sorter& sorter);

	void ClearBuffers();

	GLuint loneVAO;

	unsigned int renderSkip = 0;

  private:
	std::shared_ptr<Window> p_Window;

	Shader shader = Shader("../src/GLSL/Default.glsl");

	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);
};

} // namespace Template
