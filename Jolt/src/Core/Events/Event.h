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

	class EventDispatcher
	{
	public:
		EventDispatcher(Event* event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(std::function<bool(T)> func)
		{
			if (m_Event->GetEventType() == T::GetStaticType())
			{
				m_Event->m_Handled = func(*static_cast<T*>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event* m_Event;
	};

}