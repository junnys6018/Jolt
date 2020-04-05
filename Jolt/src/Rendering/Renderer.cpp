#include "pch.h"
#include "Renderer.h"

namespace Jolt
{
	bool Renderer::s_BeginScene = false;
	Shader* Renderer::s_ActiveShader = nullptr;
}