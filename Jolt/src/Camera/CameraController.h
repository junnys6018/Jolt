#pragma once
#include "Camera.h"
#include "Core/Events/__Events__.h"

namespace Jolt
{
	class CameraController
	{
	public:
		CameraController(glm::vec3 pos, glm::vec3 look);

		void OnUpdate(float ts);
		void OnEvent(Event* e);

		inline glm::mat4 GetViewMatrix() { return m_Camera.m_View; }
		inline glm::mat4 GetProjMatrix() { return m_Camera.m_Proj; }
		inline glm::mat4 GetViewProjMatrix() { return m_Camera.m_Proj * m_Camera.m_View; }
		inline Camera GetCamera() { return m_Camera; }

	private:
		void UpdateViewMatrix();
		void UpdateProjMatrix();

		bool OnMouseMovedEvent(MouseMovedEvent e);
		bool OnWindowResizedEvent(WindowResizeEvent e);
	private:
		Camera m_Camera;
		glm::vec3 m_Position, m_Direction, m_Right, m_Forward;
		float m_FOV, m_Aspect, m_Speed, m_Sensitivity, m_LastX, m_LastY, m_Yaw, m_Pitch;
		bool m_FirstMouse;
	};
}