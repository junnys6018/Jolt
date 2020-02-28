#include "pch.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Jolt
{
	Window* Window::Create(const char* name)
	{
		return new Window(name);
	}

	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose((GLFWwindow*)m_window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers((GLFWwindow*)GetNaitiveWindow());
	}

	Window::Window(const char* name)
	{
		m_window = glfwCreateWindow(1280, 720, name, NULL, NULL);
	}

	Window::~Window()
	{
		glfwDestroyWindow((GLFWwindow*)m_window);
		glfwTerminate();
	}
}