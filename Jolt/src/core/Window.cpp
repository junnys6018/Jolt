#include "pch.h"
#include "Window.h"
#include "GLFW/glfw3.h"

namespace Jolt
{
	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose((GLFWwindow*)m_window);
	}

	Window::Window(const char* name)
	{
		m_window = glfwCreateWindow(1280, 720, name, NULL, NULL);
	}

}