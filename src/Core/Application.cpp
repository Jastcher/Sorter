#include "Application.h"
#include "Core/Sounds.h"
#include "Event/event.h"
#include "GLFW/glfw3.h"

namespace Template
{

Application::Application(Props &&_properties) : p_Window(std::make_shared<Window>(std::move(_properties)))
{
  p_Window->SetDispatcher(
      std::make_unique<Dispatcher>(std::bind(&Application::HandleEvent, this, std::placeholders::_1)));
  p_Window->Init();
  p_Renderer    = std::make_shared<Renderer>(p_Window);
  p_Framebuffer = std::make_shared<FrameBuffer>(p_Window);
  p_SoundEngine = std::make_shared<SoundEngine>();
  p_Sorter      = std::make_shared<Sorter>(p_SoundEngine);
  p_UI          = std::make_shared<UI>(p_Window.get(), p_Sorter, p_Framebuffer, p_Renderer, p_SoundEngine);
}

Application::~Application()
{
}

void Application::HandleEvent(const Event &e)
{

  if (e.Type() == ResizeEvent::descriptor)
  {
    const ResizeEvent &resizeEvent = static_cast<const ResizeEvent &>(e);
  }
  else if (e.Type() == MouseClickEvent::descriptor)
  {
    const MouseClickEvent &mouseClickEvent = static_cast<const MouseClickEvent &>(e);
    int action                             = mouseClickEvent.action;
    int button                             = mouseClickEvent.key;
    p_Window->SetMouseState(button, action == GLFW_PRESS);
  }
  else if (e.Type() == MouseMoveEvent::descriptor)
  {
    const MouseMoveEvent &mouseMoveEvent = static_cast<const MouseMoveEvent &>(e);
    int x                                = mouseMoveEvent.x;
    int y                                = mouseMoveEvent.y;
    p_Window->mouseX                     = x;
    p_Window->mouseY                     = y;
    // std::cout << mouseMoveEvent.x << " " << mouseMoveEvent.y << std::endl;
  }
  else if (e.Type() == ScrollEvent::descriptor)
  {
    const ScrollEvent &scrollEvent = static_cast<const ScrollEvent &>(e);
  }
  else if (e.Type() == KeyEvent::descriptor)
  {
    const KeyEvent &keyEvent = static_cast<const KeyEvent &>(e);
    int action               = keyEvent.action;
    int key                  = keyEvent.keycode;

    p_Window->SetKeyState(key, action == GLFW_PRESS || action == GLFW_REPEAT);
    // std::cout << action << std::endl;
  }
}

void Application::Run()
{
  std::vector<int> data;
  for (int i = 0; i < 100; i++)
  {
    data.push_back(i);
  }

  while (!p_Window->ShouldClose())
  {
    p_SoundEngine->SetPitch(p_Sorter->props.ind1 / (float)p_Sorter->dataSize);

    p_Framebuffer->Bind();

    p_Renderer->ClearBuffers();

    p_Renderer->RenderBars(*p_Sorter.get());

    p_Framebuffer->Unbind();

    p_UI->Update();

    p_Window->Update();

    continue;
  }
}

} // namespace Template
