#include "pch.h"
#include "Instrumentor.h"

namespace Jolt
{

	Instrumentor::Instrumentor()
		:m_ProfileCount(0)
	{
	}

	void Instrumentor::BeginSession(const std::string& filepath)
	{
		m_OutputStream.open(filepath);
		WriteHeader();
	}

	void Instrumentor::EndSession()
	{
		WriteFooter();
		m_OutputStream.close();
		m_ProfileCount = 0;
	}

	void Instrumentor::WriteProfile(const ProfileData& result)
	{
		if (m_ProfileCount++ > 0)
			m_OutputStream << ",";

		std::string name = result.name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.end - result.start) << ',';
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":0" << ",";
		m_OutputStream << "\"ts\":" << result.start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	void Instrumentor::WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
		m_OutputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}
}