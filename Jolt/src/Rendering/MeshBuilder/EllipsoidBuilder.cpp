#include "pch.h"
#include "EllipsoidBuilder.h"

namespace Jolt
{
	EllipsoidBuilder::EllipsoidBuilder(float radius, uint32_t verticesPerRev)
	{
		SetDimensions(radius, radius, radius, verticesPerRev);
	}

	EllipsoidBuilder::EllipsoidBuilder(float width, float height, float depth, uint32_t verticesPerRev)
	{
		SetDimensions(width, height, depth, verticesPerRev);
	}

	void EllipsoidBuilder::SetDimensions(float width, float height, float depth, uint32_t verticesPerRev)
	{
		m_Width = width;
		m_Height = height;
		m_Depth = depth;
		m_VerticesPerRev = verticesPerRev;
	}

	Mesh EllipsoidBuilder::GenerateMesh()
	{
		// TODO: Test face culling (ie vertices are in ACW winding order)
		if (m_MeshProps == MeshProps::None)
		{
			const float x = m_Width / 2.0f;
			const float y = m_Height / 2.0f;
			const float z = m_Depth / 2.0f;

			std::vector<float> Vertices;
			Vertices.reserve(3 * m_VerticesPerRev * m_VerticesPerRev);
			for (int i_theta = 0; i_theta < m_VerticesPerRev; i_theta++)
			{
				for (int i_phi = 0; i_phi < m_VerticesPerRev; i_phi++)
				{
					float theta = M_PI * (float) i_theta / (m_VerticesPerRev - 1);
					float phi = 2 * M_PI * (float) i_phi / (m_VerticesPerRev - 1);
					Vertices.push_back(x * std::sinf(theta) * std::cosf(phi));
					Vertices.push_back(y * std::cosf(theta));
					Vertices.push_back(z * std::sinf(theta) * std::sinf(phi));
				}
			}

			/* Notes: We wrap the sphere along the x direction, but not y. 
			 * Therefore x segments require an extra row of triangles   */
			std::vector<unsigned int> Indices;
			Indices.reserve(6 * m_VerticesPerRev * (m_VerticesPerRev - 1));
			auto Idx = [&](int x, int y) -> unsigned int {return y * m_VerticesPerRev + (x % m_VerticesPerRev); };
			for (int y = 0; y < m_VerticesPerRev - 1; y++)
			{
				for (int x = 0; x < m_VerticesPerRev; x++)
				{
					Indices.push_back(Idx(x, y));
					Indices.push_back(Idx(x, y + 1));
					Indices.push_back(Idx(x + 1, y));

					Indices.push_back(Idx(x, y + 1));
					Indices.push_back(Idx(x + 1, y + 1));
					Indices.push_back(Idx(x + 1, y));
				}
			}

			auto VAO = VertexArray::Create();
			VAO->Bind();

			auto VBuf = VertexBuffer::Create(Vertices.size() * sizeof(float), Vertices.data());
			VBuf->Bind();
			VAO->SetVertexLayout({ 3 });

			auto IBuf = IndexBuffer::Create(Indices.size(), Indices.data());
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
