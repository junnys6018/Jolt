#pragma once
#include "OpenGL/Shader.h"

namespace Jolt
{
	class Light
	{
	public:
		virtual void SetUniforms(Shader& shader) = 0;
	};
}