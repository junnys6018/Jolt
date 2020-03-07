#pragma once
#include "Core/Log.h"

// Client log macros
#define LOG_TRACE(...)         ::Jolt::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          ::Jolt::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::Jolt::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::Jolt::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::Jolt::Log::GetLogger()->critical(__VA_ARGS__)

#define JOLT_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define JOLT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) 1 << x