#include "Renderer.h"
#include <cstddef>
#include <memory>

namespace Template
{

Renderer::Renderer(std::shared_ptr<Window> window) : p_Window(window)
{
	glGenVertexArrays(1, &loneVAO);
}

Renderer::~Renderer()
{
}
void Renderer::RenderBars(const Sorter& sorter)
{
	const auto& heights = sorter.data;
	shader.Activate();
	glBindVertexArray(loneVAO);

	shader.SetInt("uN", heights.size() - 1);

	shader.SetVec3("uColor", sorter.color);
	glLineWidth(1.0f);
	for(size_t i = 0; i < heights.size(); i += 1 + renderSkip)
	{
		if(i == sorter.props.ind1)
		{
			glLineWidth(6.0f);
			shader.SetVec3("uColor", green);
		}
		else if(i == sorter.props.ind2)
		{

			glLineWidth(6.0f);
			shader.SetVec3("uColor", blue);
		}
		else
		{
			glLineWidth(1.0f);

			shader.SetVec3("uColor", sorter.color);
		}

		shader.SetInt("uIndex", i);
		shader.SetInt("uHeight", heights[i]);

		glDrawArrays(GL_LINES, 0, 2);
	}
}

void Renderer::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace Template
