#pragma once
#include "pch.h"
#include "Event.h"
#include "../Layer.h"

namespace Jolt
{
	class EngineLayerEvent : public Event
	{
	public:
		inline Layer* GetLayer() { return m_Layer; }
	protected:
		EngineLayerEvent(Layer* layer)
			:m_Layer(layer)
		{

		}
		Layer* m_Layer;
	};

	class EngineLayerPoppedEvent : public EngineLayerEvent
	{
	public:
		EngineLayerPoppedEvent(Layer* layer)
			:EngineLayerEvent(layer)
		{

		}

		static EventType GetStaticType() { return EventType::EngineLayerPopped; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "EngineLayerPoppedEvent: " << m_Layer->GetName();
			return ss.str();
		}
	};

	class EngineLayerPushedEvent : public EngineLayerEvent
	{
	public:
		EngineLayerPushedEvent(Layer* layer)
			:EngineLayerEvent(layer)
		{

		}

		static EventType GetStaticType() { return EventType::EngineLayerPushed; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "EngineLayerPushedEvent: " << m_Layer->GetName();
			return ss.str();
		}
	};

	class EngineOverlayPoppedEvent : public EngineLayerEvent
	{
	public:
		EngineOverlayPoppedEvent(Layer* layer)
			:EngineLayerEvent(layer)
		{

		}

		static EventType GetStaticType() { return EventType::EngineOverlayPopped; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "EngineOverlayPoppedEvent: " << m_Layer->GetName();
			return ss.str();
		}
	};

	class EngineOverlayPushedEvent : public EngineLayerEvent
	{
	public:
		EngineOverlayPushedEvent(Layer* layer)
			:EngineLayerEvent(layer)
		{

		}

		static EventType GetStaticType() { return EventType::EngineOverlayPushed; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual std::string EventInfo() override
		{
			std::stringstream ss;
			ss << "EngineOverlayPushedEvent: " << m_Layer->GetName();
			return ss.str();
		}
	};
		
}
