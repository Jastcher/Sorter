#pragma once

#include <iostream>
#include <memory>
#include <thread>

#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Core/UI.h"

#include "Event/event.h"
#include "frameBuffer.h"

#include "Sorter.h"
#include "Sounds.h"

namespace Template
{

class Application
{
  public:
	Application(Props&& winProps);
	~Application();

	void Run();

  private:
	inline static Application* instance;

	void HandleEvent(const Event& e);

	std::shared_ptr<Dispatcher> p_Dispatcher;
	std::shared_ptr<Window> p_Window;
	std::shared_ptr<Renderer> p_Renderer;
	std::shared_ptr<UI> p_UI;
	std::shared_ptr<Sorter> p_Sorter;
	std::shared_ptr<FrameBuffer> p_Framebuffer;
	std::shared_ptr<SoundEngine> p_SoundEngine;
};

} // namespace Template
