#include "pch.h"
#include "Renderer.h"

namespace Jolt
{
	bool Renderer<LightDummy, MatDummy>::s_BeginScene = false;
	Shader* Renderer<LightDummy, MatDummy>::s_ActiveShader = nullptr;
}