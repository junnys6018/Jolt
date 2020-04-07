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

	void CPUProfiler::BeginInstrumentation(int id, fduration duration)
	{
		JOLT_ASSERT(!m_Instrument, "Instrumentation Session Already begun");
		m_Instrumentor.BeginSession();

		m_Instrument = true;
		m_ID = id;
		m_EndTime = std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(duration);
	}
}