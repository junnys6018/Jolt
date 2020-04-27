#pragma once
#include "Rendering/Mesh.h"
#include "../MeshMetaData.h"

namespace Jolt
{
	Mesh CreateFromFile(const std::string& filepath, MeshMetaData* meta_data = nullptr);
}