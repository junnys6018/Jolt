#pragma once

namespace Jolt
{
	class Window
	{
	public:
		static Window* Create(const char* name);
		inline void* GetNaitiveWindow() const { return m_window; }

		bool WindowShouldClose();
		void OnUpdate();

		~Window();
	private:
		Window(const char* name);
		void* m_window;
	};
}