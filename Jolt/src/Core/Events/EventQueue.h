#pragma once

#include "pch.h"
#include <queue>
#include "Event.h"

namespace Jolt
{

	class EventQueue
	{
	public:
		EventQueue() = default;
		EventQueue& operator=(const EventQueue&) = delete;

		void PushEvent(Event* e) { m_Queue.push(e); }
		Event* PopEvent();
	private:
		std::queue<Event*> m_Queue;
	};

}