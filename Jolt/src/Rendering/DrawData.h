#pragma once
#include "Mesh.h"
#include "glm/glm.hpp"

namespace Jolt
{
	template <typename Mat>
	class DrawData
	{
	public:
		DrawData(Mesh mesh, Mat material)
			:m_Mesh(std::move(mesh)), m_Material(material)
		{

		}

		inline void SetTransform(glm::mat4 transform)
		{
			m_Transform = transform;
		}

		friend class Renderer;
	private:
		Mesh m_Mesh;
		Mat m_Material;
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}