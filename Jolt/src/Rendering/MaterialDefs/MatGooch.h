#pragma once
#include "Rendering/Material.h"
#include "glm/glm.hpp"

namespace Jolt
{
	class MatGooch : public Material
	{
	public:
		MatGooch(glm::vec3 albedo)
			:m_Warm(glm::vec3(0.3f, 0.3f, 0.0f) + 0.25f * albedo),
			m_Cool(glm::vec3(0.0f, 0.0f, 0.55f) + 0.25f * albedo)
		{
			m_Warm = glm::clamp(m_Warm, glm::vec3(0.0f), glm::vec3(1.0f));
			m_Cool = glm::clamp(m_Cool, glm::vec3(0.0f), glm::vec3(1.0f));
		}

		virtual void SetUniforms(Shader& shader) override
		{
			shader.SetVec3("u_Warm", m_Warm);
			shader.SetVec3("u_Cool", m_Cool);
		}

	private:
		glm::vec3 m_Warm, m_Cool;
	};
}