#pragma once
#include "pch.h"
#include "Rendering/Mesh.h"

namespace Jolt
{
	enum MeshProps
	{
		None = 0,
		MeshPropsNormals = BIT(0),
		MeshPropsTextureCoords = BIT(1),
		MeshPropsTangents = BIT(2)
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
