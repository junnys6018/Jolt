#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <cassert>
#include <chrono>
using frames = std::chrono::duration<uint32_t, std::ratio<1, 60>>;
using fduration = std::chrono::duration<float, std::milli>;
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "Core/Log.h"
#include "Macro.h"

inline int HashPtr(void* ptr)
{
	return (int)std::hash<void*>{}(ptr);
}