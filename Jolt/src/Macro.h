#pragma once
#include "Core/Log.h"

// Client log macros
#define LOG_TRACE(...)         ::Jolt::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          ::Jolt::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::Jolt::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::Jolt::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::Jolt::Log::GetLogger()->critical(__VA_ARGS__)

template<typename T>
std::stringstream& print(std::stringstream& ss, const T& t)
{
	ss << t << " ";
	return ss;
}

template<typename T, typename ... Args>
std::stringstream& print(std::stringstream& ss, const T& t, const Args& ... args)
{
	ss << t << " ";
	return print(ss, args...);
}

#if defined(JOLT_DEBUG)
	#define LOG_ARGS(...)\
		std::stringstream ss;\
		print(ss, "Assertion Failed:", __VA_ARGS__);\
		LOG_ERROR(ss.str().c_str())
	#if defined(_MSC_VER)
		#define JOLT_ASSERT(x, ...) { if(!(x)) {\
			LOG_ARGS(__VA_ARGS__);\
			__debugbreak(); }}
	#elif defined(__GNUC__)
		#define JOLT_ASSERT(x, ...) { if(!(x)) {\
			LOG_ARGS(__VA_ARGS__); }}
	#endif
#else
#define JOLT_ASSERT(x, ...)
#endif

#define JOLT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) 1 << x

template<typename T, typename ... Types>
std::unique_ptr<T> CreateUnique(Types&&... Args)
{
	return std::unique_ptr<T>(T::Create(std::forward<Types>(Args)...));
}
