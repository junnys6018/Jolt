#pragma once
#include <map>
#include <string>

namespace Jolt
{
	struct MeshMetaData
	{
		std::size_t m_VertexBufferSize;
		std::size_t m_IndexCount;
		bool m_HasNormals, m_HasTexCoords;

		std::map<std::string, std::string> GetReplacementMap();
	};
}