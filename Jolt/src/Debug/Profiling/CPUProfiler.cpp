#include "pch.h"
#include "CPUProfiler.h"

namespace Jolt
{
	CPUProfiler* CPUProfiler::s_Instance = nullptr;

	void CPUProfiler::Init()
	{
		JOLT_ASSERT(!s_Instance, "CPUProfiler instance already instantiated!");
		s_Instance = new CPUProfiler();
	}

	void CPUProfiler::PushProfileResult(int id, const ProfileData& data)
	{
		m_ProfileResults[id].push_back(data);
		if (m_Instrument && (m_ID == id || m_ID == 0))
		{
			if (data.end > m_EndTime)
			{
				m_Instrumentor.EndSession();

				m_Instrument = false;
				m_ID = 0;
				m_EndTime = 0;
			}
			else
			{
				m_Instrumentor.WriteProfile(data);
			}
		}
	}

	std::map<int, std::vector<ProfileData>> CPUProfiler::GetProfileResults()
	{
		return m_ProfileResults;
	}

	void CPUProfiler::BeginInstrumentation(int id, long long duration)
	{
		JOLT_ASSERT(!m_Instrument, "Instrumentation Session Already begun");
		m_Instrumentor.BeginSession();

		m_Instrument = true;
		m_ID = id;
		m_EndTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() + duration;
	}
}