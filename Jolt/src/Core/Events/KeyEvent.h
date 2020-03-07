#pragma once
#include "pch.h"
#include "Event.h"

namespace Jolt
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keyCode)
			:m_KeyCode(keyCode)
		{

		}
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{

		}
		
		inline int GetRepeatCount() const { return m_RepeatCount; }

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode)
		{

		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			:KeyEvent(keyCode)
		{

		}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	};
}