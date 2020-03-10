#pragma once
#include "pch.h"
#include <GLFW/glfw3.h>

namespace Jolt
{
	struct MousePos
	{
		float x, y;
	};

	class Input
	{
	public:
		static void Init(GLFWwindow* window);
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static Input& Get() { return *s_Instance; }

		inline bool IsKeyPressed(int keycode) 
		{
			int state = glfwGetKey(m_Window, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		inline bool IsMouseButtonPressed(int button)
		{ 
			return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
		}

		inline MousePos GetMousePosition() 
		{ 
			double x, y;
			glfwGetCursorPos(m_Window, &x, &y);
			return { (float)x,(float)y };
		}

		inline float GetMouseX() 
		{
			auto mousePos = GetMousePosition();
			return mousePos.x;
		}

		inline float GetMouseY() 
		{
			auto mousePos = GetMousePosition();
			return mousePos.y;
		}

	private:
		Input(GLFWwindow* window);

		static Input* s_Instance;
		GLFWwindow* m_Window;
	};
}