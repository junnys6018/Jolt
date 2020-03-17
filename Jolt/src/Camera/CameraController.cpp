#include "pch.h"
#include "CameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include "Core/Application.h"
#include "Core/Input.h"

namespace Jolt
{
	CameraController::CameraController(glm::vec3 pos, glm::vec3 look)
		:m_Camera(), m_Position(pos), m_Direction(look), m_Right(glm::normalize(glm::cross(m_Direction, glm::vec3(0.0f, 1.0f, 0.0f)))),
		m_Forward(glm::vec3(m_Right.z, 0.0f, -m_Right.x)), m_FOV(60.0f), m_Aspect(0.0f), m_Speed(2.0f), m_Sensitivity(0.1f), m_LastX(0.0f),
		m_LastY(0.0f), m_Yaw(glm::degrees(glm::atan(m_Direction.z / m_Direction.x))), m_Pitch(glm::degrees(glm::asin(m_Direction.y))),
		m_FirstMouse(true)
	{
		UpdateViewMatrix();

		int width, height;
		glfwGetFramebufferSize(Application::Get().GetWindow()->GetNaitiveWindow(), &width, &height);
		m_Aspect = (float)width / height;

		UpdateProjMatrix();
	}

	void CameraController::OnUpdate(float ts)
	{
		bool moved = false;
		if (Input::Get().IsKeyPressed(GLFW_KEY_W))
		{
			m_Position += ts * m_Forward * m_Speed;
			moved = true;
		}

		if (Input::Get().IsKeyPressed(GLFW_KEY_A))
		{
			m_Position -= ts * m_Right * m_Speed;
			moved = true;
		}

		if (Input::Get().IsKeyPressed(GLFW_KEY_S))
		{
			m_Position -= ts * m_Forward * m_Speed;
			moved = true;
		}

		if (Input::Get().IsKeyPressed(GLFW_KEY_D))
		{
			m_Position += ts * m_Right * m_Speed;
			moved = true;
		}

		if (Input::Get().IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			m_Position.y -= ts * m_Speed;
			moved = true;
		}

		if (Input::Get().IsKeyPressed(GLFW_KEY_SPACE))
		{
			m_Position.y += ts * m_Speed;
			moved = true;
		}

		if (moved)
			UpdateViewMatrix();
	}

	void CameraController::OnEvent(Event* e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(JOLT_BIND_EVENT_FN(CameraController::OnMouseMovedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(JOLT_BIND_EVENT_FN(CameraController::OnWindowResizedEvent));
	}

	void CameraController::UpdateViewMatrix()
	{
		m_Camera.m_View = glm::lookAt(m_Position, m_Position + m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void CameraController::UpdateProjMatrix()
	{
		m_Camera.m_Proj = glm::perspective(glm::radians(m_FOV), m_Aspect, 0.1f, 30.0f);
	}

	bool CameraController::OnMouseMovedEvent(MouseMovedEvent e)
	{
		if (Input::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && !ImGui::GetIO().WantCaptureMouse)
		{
			float xpos = e.GetX();
			float ypos = e.GetY();
			if (m_FirstMouse) // this bool variable is initially set to true
			{
				m_LastX = xpos;
				m_LastY = ypos;
				m_FirstMouse = false;
			}
			float xoffset = xpos - m_LastX;
			float yoffset = m_LastY - ypos; // reversed since y-coordinates range from bottom to top
			m_LastX = xpos;
			m_LastY = ypos;
			// scale down offset values
			xoffset *= m_Sensitivity;
			yoffset *= m_Sensitivity;
			// Update yaw and pitch
			m_Yaw += xoffset;
			m_Pitch += yoffset;
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
			// Update camera vectors
			m_Direction.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
			m_Direction.y = sin(glm::radians(m_Pitch));
			m_Direction.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
			m_Right = glm::normalize(glm::cross(m_Direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			m_Forward = glm::vec3(m_Right.z, 0.0f, -m_Right.x);

			UpdateViewMatrix();

			return true;
		}
		m_FirstMouse = true;
		return false;
	}

	bool CameraController::OnWindowResizedEvent(WindowResizeEvent e)
	{
		if (e.GetHeight() != 0)
		{
			m_Aspect = (float)e.GetWidth() / (float)e.GetHeight();
			UpdateProjMatrix();
		}

		return false;
	}
}

