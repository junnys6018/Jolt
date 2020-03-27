#pragma once
#include "Rendering/Light.h"
#include "glm/glm.hpp"

namespace Jolt
{
	class LightPoint : public Light
	{
	public:
		LightPoint(glm::vec3 color, glm::vec3 position)
			:m_Color(color), m_Position(position)
		{

		}

		virtual void SetUniforms(Shader& shader, Camera& camera) override
		{
			shader.SetVec3("u_LightColor", m_Color);
			shader.SetVec3("u_LightPos", glm::vec3(camera.m_View * glm::vec4(m_Position, 1.0f)));
		}
	private:
		glm::vec3 m_Color;
		glm::vec3 m_Position;
	};
}