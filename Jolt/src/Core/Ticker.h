#pragma once
#include "pch.h"

// TODO: Think up better name
namespace Jolt
{
	class Ticker
	{
	public:
		using duration = fduration;

		Ticker(duration duration)
			:m_Duration(duration), m_LastActivationTime(std::chrono::steady_clock::now())
		{

		}

		inline bool IsReady()
		{
			duration elapsed_time = std::chrono::steady_clock::now() - m_LastActivationTime;
			return elapsed_time > m_Duration;
		}

		inline duration Duration() // Returns duration since last Reset call
		{
			duration elapsed_time = std::chrono::steady_clock::now() - m_LastActivationTime;
			return elapsed_time;
		}

		inline void Reset()
		{
			m_LastActivationTime = std::chrono::steady_clock::now();
		}
	private:
		duration m_Duration;
		std::chrono::time_point<std::chrono::steady_clock> m_LastActivationTime;
	};
}
