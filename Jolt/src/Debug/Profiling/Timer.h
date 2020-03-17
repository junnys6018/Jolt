#pragma once
#include <pch.h>
#include "CPUProfiler.h"

#ifdef JOLT_PROFILE
#define JOLT_PROFILE_SCOPE(name) Timer timer##__LINE__((int)std::hash<std::string>{}(this->GetName()), name)
#define JOLT_PROFILE_FUNCTION() JOLT_PROFILE_SCOPE(__FUNCSIG__)
#else
#define JOLT_PROFILE_SCOPE(name)
#define JOLT_PROFILE_FUNCTION()
#endif

namespace Jolt
{
	class Timer
	{
	public:
		Timer(int id, const char* name)
			:m_ID(id), m_Name(name), m_Stopped(false)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto end_time_point = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

			m_Stopped = true;

			float duration = (float)(end - start) * 0.001f;

			CPUProfiler::Get().PushProfileResult(m_ID, { m_Name,duration });
		}

	private:
		int m_ID;
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		bool m_Stopped;
	};
}
