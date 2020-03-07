#pragma once
#include "pch.h"
#include "Rendering/OpenGL/VertexArray.h"
#include "Rendering/OpenGL/VertexBuffer.h"
#include "Rendering/OpenGL/IndexBuffer.h"

namespace Jolt
{
	enum MeshProps
	{
		None = 0,
		MeshPropsNormals = BIT(0),
		MeshPropsTextureCoords = BIT(1),
		MeshPropsTangents = BIT(2)
	};

	struct Mesh
	{
		std::unique_ptr<VertexBuffer> VertexBuffer;
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexArray> VertexArray;
	};

	class MeshBuilder
	{
	public:
		void SetMeshProps(int props) { m_MeshProps = props; }
		virtual Mesh GenerateMesh() = 0;
	protected:
		int m_MeshProps = 0;
	};
}
