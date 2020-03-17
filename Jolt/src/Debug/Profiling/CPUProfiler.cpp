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

	void CPUProfiler::PushProfileResult(int id, ProfileData&& data)
	{
		m_ProfileResults[id].push_back(data);
	}

	const std::vector<ProfileData>& CPUProfiler::GetProfileResults(int id)
	{
		if (m_ProfileResults.find(id) == m_ProfileResults.end())
		{
			m_ProfileResults.emplace(id, std::vector<ProfileData>());
		}
		return m_ProfileResults.at(id);
	}
}