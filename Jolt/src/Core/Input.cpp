#include "pch.h"
#include "Input.h"

namespace Jolt
{
	Input* Input::s_Instance = nullptr;

	void Input::Init(GLFWwindow* window)
	{
		JOLT_ASSERT(!s_Instance, "Input instance already instantiated!");
		s_Instance = new Input(window);
	}

	Input::Input(GLFWwindow* window)
		:m_Window(window)
	{

	}
}

