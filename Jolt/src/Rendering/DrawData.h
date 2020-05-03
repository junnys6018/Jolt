#pragma once
#include "Mesh.h"
#include "MaterialDefs/MatDummy.h"
#include "LightDefs/LightDummy.h"
#include "MaterialMapper.h"

#include <glm/glm.hpp>

namespace Jolt
{
	// Forward declaration
	template<typename Light, typename Mat> class Renderer;

	template <typename Mat>
	class DrawData
	{
	public:
		DrawData(Mesh mesh, std::shared_ptr<Mat> material)
			:m_Mesh(std::move(mesh)), m_Materials(1, MaterialMapper<Mat>(material, 0, m_Mesh.m_IndexBuffer->GetCount()))
		{

		}

		DrawData(Mesh mesh, const std::vector<MaterialMapper<Mat>>& materials)
			:m_Mesh(std::move(mesh)), m_Materials(materials)
		{

		}

		inline void SetTransform(glm::mat4 transform)
		{
			m_Transform = transform;
		}

		// TODO fix: DrawData should be friends with Renderer<*, Mat> only, where * is any type
		template<class, class>
		friend class Renderer;
	private:
		Mesh m_Mesh;
		std::vector<MaterialMapper<Mat>> m_Materials;
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};

	// Class template specialisation for DrawData that has no material
	template<> class DrawData<MatDummy>
	{
	public:
		DrawData(Mesh mesh)
			:m_Mesh(std::move(mesh))
		{

		}

		inline void SetTransform(glm::mat4 transform)
		{
			m_Transform = transform;
		}

		friend class Renderer<LightDummy, MatDummy>;
	private:
		Mesh m_Mesh;
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}