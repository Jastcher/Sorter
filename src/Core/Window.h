#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Event/event.h"

#include <iostream>
#include <memory>

namespace Template
{

struct Props
{
	unsigned int width = 800;
	unsigned int height = 600;
	const char* title = "App";

	std::unique_ptr<Dispatcher> dispatcher;
};

class Window
{
  public:
	Window(Props&& propetries);
	~Window();

	bool Init();

	void Update() const;

	bool ShouldClose() const;

	// Getters for window properties
	int GetWidth() const;
	int GetHeight() const;

	void SetDispatcher(std::unique_ptr<Dispatcher>&& dispatcher);

	Props properties;

	void SetKeyState(int key, int action);
	bool GetKeyState(int key);

	void SetMouseState(int button, int action);
	bool GetMouseState(int button);

	GLFWwindow* window;

	int mouseX, mouseY;
	void SetCursorPos(double xPos, double yPos);

  private:
	std::unordered_map<int, bool> keyStates;
	std::unordered_map<int, bool> mouseStates;

	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
} // namespace Template
