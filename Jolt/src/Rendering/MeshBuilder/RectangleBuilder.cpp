#include "pch.h"
#include "RectangleBuilder.h"

namespace Jolt
{
	RectangleBuilder::RectangleBuilder(float x0, float y0, float x1, float y1)
	{
		SetDimensions(x0, y0, x1, y1);
	}

	void RectangleBuilder::SetDimensions(float x0, float y0, float x1, float y1)
	{
		m_X0 = x0;
		m_Y0 = y0;
		m_X1 = x1;
		m_Y1 = y1;
	}

	Mesh* RectangleBuilder::GenerateMesh()
	{
		if (m_MeshProps & MeshPropsNormals || m_MeshProps & MeshPropsTangents)
		{
			LOG_ERROR("Cannot generate normals or tangents in a rectangle");
		}

		static unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		if (m_MeshProps == None)
		{
			float vertex_buffer[] = {
				m_X0, m_Y0,
				m_X1, m_Y0,
				m_X1, m_Y1,
				m_X0, m_Y1
			};

			auto VAO = CreateUnique<VertexArray>();
			VAO->Bind();

			auto VBuf = CreateUnique<VertexBuffer>(sizeof(vertex_buffer), vertex_buffer);
			VBuf->Bind();
			VAO->SetVertexLayout({ 2 });

			auto IBuf = CreateUnique<IndexBuffer>(sizeof(indices) / sizeof(unsigned int), indices);
			IBuf->Bind();

			return new Mesh(VBuf.get(), IBuf.get(), VAO.get());
		}

		if (m_MeshProps & MeshPropsTextureCoords)
		{
			float vertex_buffer[] = {
				m_X0, m_Y0,    0.0f, 0.0f,
				m_X1, m_Y0,    1.0f, 0.0f,
				m_X1, m_Y1,    1.0f, 1.0f,
				m_X0, m_Y1,    0.0f, 1.0f
			};

			auto VAO = CreateUnique<VertexArray>();
			VAO->Bind();

			auto VBuf = CreateUnique<VertexBuffer>(sizeof(vertex_buffer), vertex_buffer);
			VBuf->Bind();
			VAO->SetVertexLayout({ 2,2 });

			auto IBuf = CreateUnique<IndexBuffer>(sizeof(indices) / sizeof(unsigned int), indices);
			IBuf->Bind();

			return new Mesh(VBuf.get(), IBuf.get(), VAO.get());
		}


	}
}