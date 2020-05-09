#include "pch.h"
#include "EventQueue.h"

namespace Jolt
{
	Event* EventQueue::PopEvent()
	{
		Event* ret = m_Queue.front();
		m_Queue.pop();
		return ret;
	}
}