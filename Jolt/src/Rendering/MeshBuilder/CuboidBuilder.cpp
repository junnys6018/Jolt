#include "pch.h"
#include "CuboidBuilder.h"

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
		float vertices[] = {

		}
		return Mesh();
	}
}
