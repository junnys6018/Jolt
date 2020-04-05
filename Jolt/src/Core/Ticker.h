#pragma once
#include "pch.h"

// TODO: Think up better name
class Ticker
{
public:
	Ticker(float duration) // Duration in milliseconds
		:m_Duration(duration), m_LastActivationTime(std::chrono::high_resolution_clock::now())
	{

	}

	inline bool IsReady()
	{
		std::chrono::duration<float, std::milli> elapsed_time = std::chrono::high_resolution_clock::now() - m_LastActivationTime;
		return elapsed_time.count() > m_Duration;
	}
	
	inline float Reset() // Returns duration since last Reset call
	{
		std::chrono::duration<float, std::milli> elapsed_time = std::chrono::high_resolution_clock::now() - m_LastActivationTime;
		m_LastActivationTime = std::chrono::high_resolution_clock::now();
		return elapsed_time.count();
	}
private:
	float m_Duration;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastActivationTime;
};
