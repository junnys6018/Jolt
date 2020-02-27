#include "pch.h"
#include "Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Jolt
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const char* name)
	{
		assert(!s_Instance);
		s_Instance = this;

		assert(glfwInit());
		m_Window = std::make_unique<Window>(name);
		glfwMakeContextCurrent((GLFWwindow*)m_Window->GetNaitiveWindow());
		glfwSwapInterval(1); // Enable vsync

		gladLoadGL();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
}

