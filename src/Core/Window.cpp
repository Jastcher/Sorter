#include "Window.h"
#include "Event/event.h"

namespace Template
{

Window::Window(Props&& _Properties) : properties(std::move(_Properties))
{
}

Window::~Window()
{
}

bool Window::Init()
{
	if(!glfwInit())
	{
		std::cout << "glfw init failed" << std::endl;
		glfwTerminate();
		return 0;
	}

	window = glfwCreateWindow(properties.width, properties.height, properties.title, NULL, NULL);
	if(!window)
	{
		std::cout << "window failed to create" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 16);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to init glad" << std::endl;
		return 0;
	}

	glViewport(0, 0, properties.width, properties.height);

	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glfwSetWindowUserPointer(window, &properties);

	glLineWidth(4.0f);

	return 1;
}

int Window::GetWidth() const
{
	return properties.width;
}
int Window::GetHeight() const
{
	return properties.height;
}
void Window::SetDispatcher(std::unique_ptr<Dispatcher>&& dispatcher)
{
	properties.dispatcher = std::move(dispatcher);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(window) == GLFW_TRUE;
}

void Window::Update() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::SetKeyState(int key, int action)
{
	keyStates[key] = action;
}

bool Window::GetKeyState(int key)
{
	return keyStates[key];
}

void Window::SetMouseState(int button, int action)
{
	mouseStates[button] = action;
}

bool Window::GetMouseState(int button)
{
	return mouseStates[button];
}
void Window::SetCursorPos(double xPos, double yPos)
{
	glfwSetCursorPos(window, xPos, yPos);
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
	KeyEvent event;
	event.keycode = key;
	event.action = action;

	Props& properties = *(Props*)glfwGetWindowUserPointer(window);
	properties.dispatcher->Post(event);
}

void Window::ErrorCallback(int error, const char* description)
{
	std::cerr << "[ERROR] " << error << " -> " << description << std::endl;
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	MouseClickEvent event;
	event.key = button;
	event.action = action;

	Props& properties = *(Props*)glfwGetWindowUserPointer(window);
	properties.dispatcher->Post(event);
}

void Window::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	MouseMoveEvent event;
	event.x = xpos;
	event.y = ypos;

	Props& properties = *(Props*)glfwGetWindowUserPointer(window);
	properties.dispatcher->Post(event);
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	ResizeEvent event;
	event.width = width;
	event.height = height;

	Props& properties = *(Props*)glfwGetWindowUserPointer(window);
	properties.dispatcher->Post(event);

	properties.width = width;
	properties.height = height;
	glViewport(0, 0, width, height);
}

void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ScrollEvent event;
	event.scrollX = xoffset;
	event.scrollY = yoffset;

	Props& properties = *(Props*)glfwGetWindowUserPointer(window);
	properties.dispatcher->Post(event);
}

} // namespace Template
