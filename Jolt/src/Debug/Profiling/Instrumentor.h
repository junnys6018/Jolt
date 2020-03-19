#pragma once
#include <fstream>
#include "ProfileData.h"

namespace Jolt
{
	class Instrumentor
	{
	public:
		Instrumentor();

		void BeginSession(const std::string& filepath = "results.json");
		void EndSession();

		void WriteProfile(const ProfileData& result);

	private:
		void WriteHeader();
		void WriteFooter();

	private:
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};
}