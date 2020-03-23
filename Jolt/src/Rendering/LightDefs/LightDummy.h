#pragma once
#include "Rendering/Light.h"

namespace Jolt
{
	class LightDummy : public Light	
	{
	public:
		virtual void SetUniforms(Shader& shader) override
		{

		}
	};
}