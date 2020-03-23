#pragma once
#include "OpenGL/Shader.h"

namespace Jolt
{
	class Material
	{
	public:
		virtual void SetUniforms(Shader& shader) = 0;
	};
}