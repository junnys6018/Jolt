#pragma once
#include "pch.h"
#include "Instrumentor.h"
#include "ProfileData.h"

namespace Jolt
{
	class CPUProfiler
	{
	public:
		static void Init();
		inline static CPUProfiler& Get() { return *s_Instance; }

		CPUProfiler(const CPUProfiler&) = delete;
		CPUProfiler& operator=(const CPUProfiler&) = delete;

		void PushProfileResult(int id, ProfileData&& data);
		const std::vector<ProfileData>& GetProfileResults(int id);

		void BeginInstrumentation(int id, long long duration);

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