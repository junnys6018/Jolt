#pragma once

namespace Jolt
{
	struct ProfileData
	{
		using time_point = std::chrono::time_point<std::chrono::steady_clock>;

		const char* name;
		time_point start, end;
	};

}