#pragma once
#include <GLFW/glfw3.h>
#include "Events/Event.h"

namespace Jolt
{
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event*)>;
		static Window* Create(const char* name);
		inline GLFWwindow* GetNaitiveWindow() const { return m_Window; }

		bool WindowShouldClose();
		void OnUpdate();
		void SetEventCallback(const EventCallbackFn& fn);

		~Window();
	private:
		Window(const char* name);
		GLFWwindow* m_Window;
	};
}