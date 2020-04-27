#pragma once

#include "Rendering/Renderer.h"
#include "Rendering/Mesh.h"
#include "Rendering/MeshMetaData.h"

#include "Rendering/Light.h"
#include "Rendering/LightDefs/LightDummy.h"
#include "Rendering/LightDefs/LightPoint.h"

#include "Rendering/Material.h"
#include "Rendering/MaterialDefs/MatDummy.h"
#include "Rendering/MaterialDefs/MatGooch.h"


namespace Jolt
{
	// Pre defined renderers
	using GoochRenderer = Renderer<LightPoint, MatGooch>;
	using FlatColorRenderer = Renderer<LightDummy, MatDummy>;
}