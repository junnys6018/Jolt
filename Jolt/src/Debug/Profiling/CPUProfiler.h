#pragma once
#include "pch.h"

namespace Jolt
{
	struct ProfileData
	{
		const char* name;
		float duration;
	};

	class CPUProfiler
	{
	public:
		static void Init();
		inline static CPUProfiler& Get() { return *s_Instance; }

		CPUProfiler(const CPUProfiler&) = delete;
		CPUProfiler& operator=(const CPUProfiler&) = delete;

		void PushProfileResult(int id, ProfileData&& data);
		const std::vector<ProfileData>& GetProfileResults(int id);
		inline void Clear() { m_ProfileResults.clear(); }
	private:
		std::map<int, std::vector<ProfileData>> m_ProfileResults;
		static CPUProfiler* s_Instance;

		CPUProfiler() = default;
	};
}