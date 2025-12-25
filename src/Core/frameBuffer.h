#pragma once
#include "Window.h"
#include <memory>

namespace Template
{

class FrameBuffer
{
  public:
	unsigned int id;
	unsigned int textureColorbuffer;
	unsigned int rbo;

	int oldWidth;
	int oldHeight;

	FrameBuffer(std::shared_ptr<Window> window);
	void Resize(int width, int height);
	void SetSize(int width, int height);

	void Bind();
	void Unbind();
};
} // namespace Template
