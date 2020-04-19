#pragma once
#include "pch.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Jolt
{
	class CubeMap
	{
	public:
		static CubeMap* Create(std::array<std::string, 6> faces);

		void Bind(GLuint slot) const;
		void UnBind() const;

		~CubeMap();

	private:
		CubeMap() = default;
		GLuint m_ID;
	};

	void DrawCubeMap(const CubeMap& cubeMap, const glm::mat4& VP);
}