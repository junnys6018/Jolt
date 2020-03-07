#pragma once
#include "pch.h"

namespace Jolt
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, // Implemented in ApplicationEvent.h
		KeyPressed, KeyReleased, KeyTyped, // Implemented in KeyEvent.h
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled // Implemented in MouseEvent.h
	};

	class Event
	{
	public:
		bool m_Handled = false;

		virtual EventType GetEventType() = 0;
		virtual std::string EventInfo() = 0;
	};

}