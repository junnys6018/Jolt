#include "pch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Application.h"
#include "Rendering/OpenGL/OpenGLDebug.h"


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
		:m_LastFrameTime(0.0f), m_FPS(60.0f)
	{
		JOLT_ASSERT(!s_Instance, "Application Instance already instantiated!");
		s_Instance = this;

		Log::Init();

		JOLT_ASSERT(glfwInit() == GLFW_TRUE, "GLFW Failed to initialize");
		m_Window = std::unique_ptr<Window>(Window::Create(name));
		m_Window->SetEventCallback(JOLT_BIND_EVENT_FN(Application::OnEventCallback));
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
		int FrameCount = 0;
		float LastFPSTimer = glfwGetTime();
		while (!m_Window->WindowShouldClose())
		{
			float time = (float)glfwGetTime();
			float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time; 

			FrameCount++;
			if (time - LastFPSTimer > 1.0f)
			{
				m_FPS = FrameCount;
				FrameCount = 0;
				LastFPSTimer = time;
			}

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			ImGuiBeginFrame();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			ImGuiEndFrame();

			m_Window->OnUpdate();
			ProcessEventQueue();
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

	void Application::ProcessEventQueue()
	{
		while (Event* e = m_EventQueue.PopEvent())
		{
			for (Layer* layer : m_LayerStack)
			{
				layer->OnEvent(e);
				if (e->m_Handled)
					break;
			}

			// LOG_INFO(e->EventInfo());
			EventDispatcher dispatch(e);
			dispatch.Dispatch<WindowResizeEvent>([](WindowResizeEvent e) -> bool
			{
				glViewport(0, 0, e.GetWidth(), e.GetHeight());
				return true;
			});

			// TODO: Implement Event data pool instead of heap allocating every event
			delete e;
		}
	}
}

