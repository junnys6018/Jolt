#pragma once
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Core/ImGui/ImGuiBuild.h"

#include <memory>

namespace Jolt
{
	class Application
	{
	public:
		Application(const char* name);
		virtual ~Application();

		void Run();

		inline Window* GetWindow() { return m_Window.get(); }
		inline static Application& Get() { return *s_Instance; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		float m_LastFrameTime;

		static Application* s_Instance;
	};
}