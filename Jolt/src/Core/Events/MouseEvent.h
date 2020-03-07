#pragma once
#include "pch.h"
#include "Event.h"

namespace Jolt
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y)
		{

		}

		inline float GetX() { return m_MouseX; }
		inline float GetY() { return m_MouseY; }

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
	};
}