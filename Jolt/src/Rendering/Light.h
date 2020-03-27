#pragma once
#include "OpenGL/Shader.h"
#include "Camera/Camera.h"

namespace Jolt
{
	class Light
	{
	public:
		virtual void SetUniforms(Shader& shader, Camera& camera) = 0;
	};
}