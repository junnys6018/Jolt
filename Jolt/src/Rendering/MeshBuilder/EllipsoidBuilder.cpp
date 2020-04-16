#include "pch.h"
#include "EllipsoidBuilder.h"

namespace Jolt
{
	EllipsoidBuilder::EllipsoidBuilder(float radius, uint32_t verticesPerRev)
		:m_Width(radius), m_Height(radius), m_Depth(radius), m_VerticesPerRev(verticesPerRev)
	{

	}

	EllipsoidBuilder::EllipsoidBuilder(float width, float height, float depth, uint32_t verticesPerRev)
		: m_Width(width), m_Height(height), m_Depth(depth), m_VerticesPerRev(verticesPerRev)
	{

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
		const float x = m_Width / 2.0f;
		const float y = m_Height / 2.0f;
		const float z = m_Depth / 2.0f;

		std::vector<float> Vertices;
		int floats_per_vertex = 3;
		if (m_MeshProps & MeshPropsNormals)
			floats_per_vertex += 3;
		if (m_MeshProps & MeshPropsTangents)
			floats_per_vertex += 3;
		if (m_MeshProps & MeshPropsTextureCoords)
			floats_per_vertex += 2;

		Vertices.reserve((size_t)floats_per_vertex * m_VerticesPerRev * m_VerticesPerRev);
		for (uint32_t i_theta = 0; i_theta < m_VerticesPerRev; i_theta++)
		{
			for (uint32_t i_phi = 0; i_phi < m_VerticesPerRev; i_phi++)
			{
				float theta = (float)M_PI * (float) i_theta / (m_VerticesPerRev - 1);
				float phi = 2 * (float)M_PI * (float) i_phi / (m_VerticesPerRev - 1);
				Vertices.push_back(x * sinf(theta) * cosf(phi));
				Vertices.push_back(y * cosf(theta));
				Vertices.push_back(z * sinf(theta) * sinf(phi));
				if (m_MeshProps & MeshPropsTextureCoords)
				{
					Vertices.push_back(1.0f - (float)i_phi / (float)(m_VerticesPerRev - 1));
					Vertices.push_back(1.0f - (float)i_theta / (float)(m_VerticesPerRev - 1));
				}
			}
		}

		/* Notes: We wrap the sphere along the x direction, but not y. 
		 * Therefore x segments require an extra row of triangles   */
		std::vector<GLuint> Indices;
		Indices.reserve((size_t)6 * m_VerticesPerRev * (m_VerticesPerRev - 1));
		auto Idx = [&](int x, int y) -> unsigned int {return y * m_VerticesPerRev + (x % m_VerticesPerRev); };
		for (uint32_t y = 0; y < m_VerticesPerRev - 1; y++)
		{
			for (uint32_t x = 0; x < m_VerticesPerRev; x++)
			{
				Indices.push_back(Idx(x, y));
				Indices.push_back(Idx(x + 1, y));
				Indices.push_back(Idx(x, y + 1));

				Indices.push_back(Idx(x, y + 1));
				Indices.push_back(Idx(x + 1, y));
				Indices.push_back(Idx(x + 1, y + 1));
			}
		}

		auto VAO = VertexArray::Create();
		VAO->Bind();

		auto VBuf = VertexBuffer::Create(Vertices.size() * sizeof(float), Vertices.data());
		VBuf->Bind();
		VertexLayout layout = (m_MeshProps & MeshPropsTextureCoords) ? VertexLayout({ 3, 2 }) : VertexLayout({ 3 });
		VAO->SetVertexLayout(layout);

		auto IBuf = IndexBuffer::Create((GLsizei)Indices.size(), Indices.data());
		IBuf->Bind();

		return Mesh(VBuf, IBuf, VAO);
	}
}
