#include "pch.h"
#include "MeshMetaData.h"

using namespace std::literals::string_literals;

namespace Jolt
{
	std::map<std::string, std::string> MeshMetaData::GetReplacementMap()
	{
		static std::map<std::string, std::string> map = {
			{"attrib.tex"s, m_HasTexCoords ? "1" : "-1"},
			{"attrib.norm"s, m_HasNormals ? (m_HasTexCoords ? "2" : "1") : "-1" }
		};
		return map;
	}
}