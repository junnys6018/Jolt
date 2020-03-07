#include "pch.h"
#include "EventQueue.h"

namespace Jolt
{
	Event* EventQueue::PopEvent()
	{
		{
			if (m_Queue.size() != 0)
			{
				Event* ret = m_Queue.front();
				m_Queue.pop();
				return ret;
			}
			else
				return nullptr;
		}
	}
}