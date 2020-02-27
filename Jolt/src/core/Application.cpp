#include "pch.h"
#include "Application.h"
#include "OpenGL/OpenGLDebug.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Jolt
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const char* name)
		:m_LastFrameTime(0.0f)
	{
		assert(!s_Instance);
		s_Instance = this;

		assert(glfwInit());
		m_Window = std::make_unique<Window>(name);
		glfwMakeContextCurrent((GLFWwindow*)m_Window->GetNaitiveWindow());
		glfwSwapInterval(1); // Enable vsync

		gladLoadGL();

		EnableGLDebugging();
		ImGuiInit();
	}

	Application::~Application()
	{
		ImGuiDestroy();
	}

	void Application::Run()
	{
		while (!m_Window->WindowShouldClose())
		{
			float time = (float)glfwGetTime();
			float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			ImGuiBeginFrame();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			ImGuiEndFrame();

			m_Window->OnUpdate();
		}
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

