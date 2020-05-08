#pragma once
#include "pch.h"
#include "Instrumentor.h"
#include "ProfileData.h"

namespace Jolt
{
	class CPUProfiler
	{
	public:
		CPUProfiler(const CPUProfiler&) = delete;
		CPUProfiler& operator=(const CPUProfiler&) = delete;
		static void Init();

		void PushProfileResult(int id, const ProfileData& data);
		const std::map<int, std::vector<ProfileData>>& GetProfileResults();

		void BeginInstrumentation(int id, fduration duration);

		inline static CPUProfiler& Get() { return *s_Instance; }
		inline void Clear() { m_ProfileResults.clear(); }
	private:
		std::map<int, std::vector<ProfileData>> m_ProfileResults;
		static CPUProfiler* s_Instance;

		Instrumentor m_Instrumentor;
		bool m_Instrument = false;
		int m_ID = 0;
		ProfileData::time_point m_EndTime;

		CPUProfiler() = default;
	};
}