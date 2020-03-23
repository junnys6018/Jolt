#pragma once
#include "Rendering/Material.h"

namespace Jolt
{
	class MatDummy : public Material
	{
	public:
		virtual void SetUniforms(Shader& shader) override
		{

		}
	};
}