#include "pch.h"
#include "Application.h"
#include "OpenGL/OpenGLDebug.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Jolt
{
	Application* Application::s_Instance = nullptr;

	static void PrintSystemInfomation()
	{
		LOG_INFO("OpenGL Info:");
		LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
		LOG_INFO("  GLFW Version: {0}", glfwGetVersionString());
	}

	Application::Application(const char* name)
		:m_LastFrameTime(0.0f)
	{
		JOLT_ASSERT(!s_Instance, "Application Instance already instantiated!");
		s_Instance = this;

		Log::Init();

		JOLT_ASSERT(glfwInit() == GLFW_TRUE, "GLFW Failed to initialize");
		m_Window = std::make_unique<Window>(name);
		glfwMakeContextCurrent((GLFWwindow*)m_Window->GetNaitiveWindow());
		glfwSwapInterval(1); // Enable vsync

		gladLoadGL();

		PrintSystemInfomation();
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

