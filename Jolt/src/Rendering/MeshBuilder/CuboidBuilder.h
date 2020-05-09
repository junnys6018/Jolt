#pragma once
#include "MeshBuilder.h"

namespace Jolt
{
	class CuboidBuilder : public MeshBuilder
	{
	public:
		CuboidBuilder(float sideLength);
		CuboidBuilder(float width, float height, float depth);

		void SetDimensions(float width, float height, float depth);

		virtual Mesh* GenerateMesh() override;

	private:
		float m_Width = 1.0f, m_Height = 1.0f, m_Depth = 1.0f;
	};
}