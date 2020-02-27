#pragma once

namespace Jolt
{
	class Window
	{
	public:
		Window(const char* name);
		inline void* GetNaitiveWindow() const { return m_window; }

		bool WindowShouldClose();
	private:
		void* m_window;
	};
}