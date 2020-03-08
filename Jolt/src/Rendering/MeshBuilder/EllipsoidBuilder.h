#pragma once
#include "MeshBuilder.h"

namespace Jolt
{
	class EllipsoidBuilder : MeshBuilder
	{
	public:
		EllipsoidBuilder(float radius, uint32_t verticesPerRev = 32);
		EllipsoidBuilder(float width, float height, float depth, uint32_t verticesPerRev = 32);

		void SetDimensions(float width, float height, float depth, uint32_t verticesPerRev);

		virtual Mesh GenerateMesh() override;

	private:
		float m_Width = 1.0f, m_Height = 1.0f, m_Depth = 1.0f;
		uint32_t m_VerticesPerRev;
	};
}