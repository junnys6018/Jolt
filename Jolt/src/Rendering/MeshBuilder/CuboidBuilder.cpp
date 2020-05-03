#include "pch.h"
#include "CuboidBuilder.h"

#include <glm/glm.hpp>
using namespace glm;

namespace Jolt
{
	CuboidBuilder::CuboidBuilder(float sideLength)
	{
		SetDimensions(sideLength, sideLength, sideLength);
	}

	CuboidBuilder::CuboidBuilder(float width, float height, float depth)
	{
		SetDimensions(width, height, depth);
	}

	void CuboidBuilder::SetDimensions(float width, float height, float depth)
	{
		m_Width = width;
		m_Height = height;
		m_Depth = depth;
	}

	Mesh CuboidBuilder::GenerateMesh()
	{
		// TODO: Test face culling (ie vertices are in ACW order)
		if (m_MeshProps == MeshProps::None)
		{
			float x = m_Width / 2.0f;
			float y = m_Height / 2.0f;
			float z = m_Depth / 2.0f;
			float vertices[] = {
				-x, -y, -z,
				-x, -y,  z,
				-x,  y,  z,
				-x,  y, -z,
				 x, -y, -z,
				 x, -y,  z,
				 x,  y,  z,
				 x,  y, -z,
			};

			static unsigned int indices[] = {
				// -x face
				0, 1, 2,
				0, 2, 3,
				// +x face
				4, 6, 5,
				4, 7, 6,
				// -y face
				1, 0, 4,
				1, 4, 5,
				// +y face
				2, 7, 3,
				2, 6, 7,
				// -z face
				0, 3, 7,
				0, 7, 4,
				// +z face
				1, 6, 2,
				1, 5, 6
			};

			auto VAO = VertexArray::Create();
			VAO->Bind();

			auto VBuf = VertexBuffer::Create(sizeof(vertices), vertices);
			VBuf->Bind();
			VAO->SetVertexLayout({ 3 });

			auto IBuf = IndexBuffer::Create(sizeof(indices) / sizeof(unsigned int), indices);
			IBuf->Bind();
			
			return Mesh(VBuf, IBuf, VAO);
		}
		else
		{
			// TODO: 
			LOG_CRITICAL("HAVENT IMPLEMENTED VERTEX ATTRIBUTES");
		}
		return Mesh();
	}
}