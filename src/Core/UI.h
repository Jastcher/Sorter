#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <memory>
#include <thread>

#include "Window.h"
#include "Sorter.h"
#include "frameBuffer.h"
#include "Renderer/Renderer.h"
#include "Core/Sounds.h"

namespace Template
{

class UI
{

  public:
	UI();
	UI(Window* window,
	   std::shared_ptr<Sorter> _sorter,
	   std::shared_ptr<FrameBuffer> _frameBuffer,
	   std::shared_ptr<Renderer> _renderer,
	   std::shared_ptr<SoundEngine> _soundEngine);

	~UI();

	void Update();

	std::shared_ptr<Sorter> sorter;
	std::shared_ptr<FrameBuffer> frameBuffer;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<SoundEngine> soundEngine;
};

} // namespace Template
