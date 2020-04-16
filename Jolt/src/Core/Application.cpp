#include "pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Rendering/OpenGL/OpenGLDebug.h"
#include "Input.h"
#include "Debug/Profiling/Timer.h"


namespace Jolt
{
	// TODO move function to new file
	void error_callback(int code, const char* description)
	{
		LOG_ERROR("GLFW error: {}", description);
	}

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
		:m_ImGuiOverlay(), m_DebugOverlay(), m_LastFrameTime(0.0f), m_FPS(60.0f), m_Ticker(std::chrono::seconds(1))
	{
		JOLT_ASSERT(!s_Instance, "Application Instance already instantiated!");
		s_Instance = this;

		Log::Init();
#ifdef JOLT_PROFILE
		CPUProfiler::Init();
#endif

		JOLT_ASSERT(glfwInit() == GLFW_TRUE, "GLFW Failed to initialize");
		glfwSetErrorCallback(error_callback);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		m_Window = CreateUnique<Window>(name);
		m_Window->SetEventCallback(JOLT_BIND_EVENT_FN(Application::OnEventCallback));
		glfwMakeContextCurrent(m_Window->GetNaitiveWindow());
		glfwSwapInterval(1); // Enable vsync

		// Load all OpenGL functions using the glfw loader function
		JOLT_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize OpenGL functions")

		Input::Init(m_Window->GetNaitiveWindow());

		PrintSystemInfomation();
		EnableGLDebugging();
		m_LayerStack.PushOverlay(&m_ImGuiOverlay);
		m_LayerStack.PushOverlay(&m_DebugOverlay);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		int FrameCount = 0;
		while (!m_Window->WindowShouldClose())
		{
			JOLT_PROFILE_FUNCTION();

			float time = (float)glfwGetTime();
			float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			FrameCount++;
			if (m_Ticker.IsReady()) // Update every second
			{
				Ticker::duration duration = m_Ticker.Duration();
				m_Ticker.Reset();
				m_FPS = (float)FrameCount / duration.count() * 1000.0f;
				FrameCount = 0;
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiOverlay.Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiOverlay.End();

			m_Window->OnUpdate();
			ProcessEventQueue();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		OnEventCallback(new EngineLayerPushedEvent(layer));
	}

	void Application::PushOverlay(Layer* overlay)
	{
		OnEventCallback(new EngineOverlayPushedEvent(overlay));
	}

	void Application::PopLayer(Layer* layer)
	{
		OnEventCallback(new EngineLayerPoppedEvent(layer));
	}

	void Application::PopOverlay(Layer* overlay)
	{
		OnEventCallback(new EngineOverlayPoppedEvent(overlay));
	}

	void Application::ProcessEventQueue()
	{
		while (Event* e = m_EventQueue.PopEvent())
		{
			EventDispatcher dispatch(e);
			dispatch.Dispatch<WindowResizeEvent>([](WindowResizeEvent e) -> bool
			{
				glViewport(0, 0, e.GetWidth(), e.GetHeight());
				return false;
			});

			dispatch.Dispatch<EngineLayerPushedEvent>([this](EngineLayerPushedEvent e) -> bool
			{
				m_LayerStack.PushLayer(e.GetLayer());
				return false;
			});

			dispatch.Dispatch<EngineOverlayPushedEvent>([this](EngineOverlayPushedEvent e) -> bool
			{
				m_LayerStack.PushOverlay(e.GetLayer());
				return false;
			});
			dispatch.Dispatch<EngineLayerPoppedEvent>([this](EngineLayerPoppedEvent e) -> bool
			{
				m_LayerStack.PopLayer(e.GetLayer());
				return false;
			});

			dispatch.Dispatch<EngineOverlayPoppedEvent>([this](EngineOverlayPoppedEvent e) -> bool
			{
				m_LayerStack.PopOverlay(e.GetLayer());
				return false;
			});


			for (Layer* layer : m_LayerStack)
			{
				if (e->m_Handled)
					break;
				layer->OnEvent(e);
			}

			//LOG_INFO(e->EventInfo());

			// TODO: Implement Event data pool instead of heap allocating every event
			delete e;
		}
	}
}

