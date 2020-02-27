#pragma once
#include "Jolt.h"

namespace Jolt
{
	class Application
	{
	public:
		Application(const char* name);
		virtual ~Application() = default;

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;


		static Application* s_Instance;
	};
}