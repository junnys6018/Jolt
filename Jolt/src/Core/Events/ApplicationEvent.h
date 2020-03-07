#pragma once
#include "pch.h"
#include "Event.h"

namespace Jolt
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			return std::string("WindowCloseEvent");
		}
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			:m_Width(width), m_Height(height)
		{

		}

		inline uint32_t GetWidth() { return m_Width; }
		inline uint32_t GetHeight() { return m_Height; }

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}
	private:
		uint32_t m_Width, m_Height;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		static EventType GetStaticType() { return EventType::WindowFocus; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			return std::string("WindowFocusEvent");
		}
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		static EventType GetStaticType() { return EventType::WindowLostFocus; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			return std::string("WindowLostFocusEvent");
		}
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int posX, int posY)
			:m_PosX(posX), m_PosY(posY)
		{

		}

		inline int GetX() { return m_PosX; }
		inline int GetY() { return m_PosY; }

		static EventType GetStaticType() { return EventType::WindowMoved; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent: (" << m_PosX << ", " << m_PosY << ")";
			return ss.str();
		}
	private:
		int m_PosX, m_PosY;
	};
}