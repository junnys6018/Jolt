#pragma once
#include <pch.h>
#include "CPUProfiler.h"

#ifdef JOLT_PROFILE
#define JOLT_PROFILE_SCOPE(name) Timer timer##__LINE__((int)std::hash<void*>{}((void*)this), name)
#define JOLT_PROFILE_FUNCTION() JOLT_PROFILE_SCOPE(__FUNCTION__)
#else
#define JOLT_PROFILE_SCOPE(name)
#define JOLT_PROFILE_FUNCTION()
#endif

namespace Jolt
{
	class Timer
	{
	public:
		using time_point = std::chrono::time_point<std::chrono::steady_clock>;

		Timer(int id, const char* name)
			:m_ID(id), m_Name(name), m_Stopped(false)
		{
			m_StartTimePoint = std::chrono::steady_clock::now();
		}

		~Timer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			time_point end_time_point = std::chrono::steady_clock::now();

			m_Stopped = true;

			CPUProfiler::Get().PushProfileResult(m_ID, { m_Name,m_StartTimePoint,end_time_point });
		}

	private:
		int m_ID;
		const char* m_Name;
		time_point m_StartTimePoint;
		bool m_Stopped;
	};
}
