#pragma once
#include "MeshBuilder.h"

namespace Jolt
{
	class RectangleBuilder : public MeshBuilder
	{
	public:
		// Coordinates of rectangle specified in NDC
		RectangleBuilder(float x0 = -1.0f, float y0 = -1.0f, float x1 = 1.0f, float y1 = 1.0f);

		void SetDimensions(float x0, float y0, float x1, float y1);

		virtual Mesh* GenerateMesh() override;

	private:
		float m_X0 = -1.0f, m_Y0 = -1.0f, m_X1 = 1.0f, m_Y1 = 1.0f;
	};
}