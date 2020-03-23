#pragma once

// Main header file. Include in application for library access

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../vendor/imgui/imgui.h"

#include "Core/Application.h"

#include "Rendering/OpenGL/__OpenGL__.h"
#include "Rendering/MeshBuilder/__MeshBuilder__.h"
#include "Rendering/__Rendering__.h"

#include "Core/Events/__Events__.h"
#include "Core/Input.h"
#include "Camera/CameraController.h"

#include "Debug/Profiling/Timer.h"
