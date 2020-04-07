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
		m_OutputStream << "\"dur\":" << std::chrono::duration<float,std::micro>(result.end - result.start).count() << ',';
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":0" << ",";
		m_OutputStream << "\"ts\":" << std::chrono::duration_cast<std::chrono::microseconds>(result.start.time_since_epoch()).count();
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