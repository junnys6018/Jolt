#include "pch.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Jolt
{
	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose((GLFWwindow*)m_window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers((GLFWwindow*)Application::Get().GetWindow().GetNaitiveWindow());
	}

	Window::Window(const char* name)
	{
		m_window = glfwCreateWindow(1280, 720, name, NULL, NULL);
	}

}