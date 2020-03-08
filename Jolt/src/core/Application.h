#pragma once
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Core/ImGui/ImGuiBuild.h"
#include "Core/Events/__Events__.h"

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
		inline float GetFPS() { return m_FPS; }
		inline static Application& Get() { return *s_Instance; }
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		/* Event Handling */
		void OnEventCallback(Event* e) { m_EventQueue.PushEvent(e); }
		void ProcessEventQueue();
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		EventQueue m_EventQueue;

		std::vector<Layer*> m_RemoveLayers;
		std::vector<Layer*> m_RemoveOverlays;

		float m_LastFrameTime, m_FPS;

		static Application* s_Instance;
	};
}