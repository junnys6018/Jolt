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
		std::map<int, std::vector<ProfileData>> GetProfileResults();

		void BeginInstrumentation(int id, long long duration);

		inline static CPUProfiler& Get() { return *s_Instance; }
		inline void Clear() { m_ProfileResults.clear(); }
	private:
		std::map<int, std::vector<ProfileData>> m_ProfileResults;
		static CPUProfiler* s_Instance;

		Instrumentor m_Instrumentor;
		bool m_Instrument;
		int m_ID;
		long long m_EndTime;

		CPUProfiler() = default;
	};
}