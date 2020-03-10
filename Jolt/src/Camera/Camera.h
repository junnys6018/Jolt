#pragma once
#include <glm/glm.hpp>

namespace Jolt
{
	struct Camera
	{
		glm::mat4 m_View;
		glm::mat4 m_Proj;
	};
}