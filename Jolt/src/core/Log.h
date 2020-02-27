#pragma once
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Jolt {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// Client log macros
#define LOG_TRACE(...)         ::Jolt::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          ::Jolt::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::Jolt::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::Jolt::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::Jolt::Log::GetLogger()->critical(__VA_ARGS__)

#define JOLT_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }