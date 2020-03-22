#pragma once
#include "Jolt.h"

using namespace Jolt;

class ExampleLayer2 : public Layer
{
public:
	ExampleLayer2()
		:Layer("Example 2"), m_ClearColor(0.0f), m_Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
			m_Rotating(false), m_Angle(0.0f), m_RotateSpeed(1.0f)
	{

	}

	virtual void OnAttach() override
	{
		glEnable(GL_DEPTH_TEST);

		m_Mesh = CreateFromFile("data");
		m_CubeShader = std::unique_ptr<Shader>(Shader::CreateFromFile("Cube.glsl"));
	}

	virtual void OnDetach() override
	{
		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	virtual void OnUpdate(float ts) override
	{
		JOLT_PROFILE_FUNCTION();

		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f);
		{
			JOLT_PROFILE_SCOPE("CameraController::OnUpdate");
			m_Camera.OnUpdate(ts);
		}
		if (m_Rotating)
		{
			m_Angle += ts * m_RotateSpeed;
		}

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
		model = glm::rotate(model, m_Angle, glm::vec3(1.0f, 1.0, 0.0f));

		m_CubeShader->Bind();
		m_CubeShader->SetMat4("u_MVP", m_Camera.GetViewProjMatrix() * model);

		m_Mesh.VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_Mesh.IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
	}

	virtual void OnImGuiRender() override
	{
		JOLT_PROFILE_FUNCTION();
		ImGui::Begin("test");

		ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]);
		ImGui::SliderFloat("Rotate Speed", &m_RotateSpeed, 0.1f, 5.0f);
		ImGui::Text("Press 'R' to Rotate");

		ImGui::End();
	}

	virtual void OnEvent(Event* e) override
	{
		m_Camera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(JOLT_BIND_EVENT_FN(ExampleLayer2::OnKeyPressedEvent));
	}

private:
	glm::vec3 m_ClearColor;
	std::unique_ptr<Shader> m_CubeShader;
	Mesh m_Mesh;
	CameraController m_Camera;

	bool m_Rotating;
	float m_Angle, m_RotateSpeed;

private:
	bool OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == JOLT_KEY_R)
		{
			m_Rotating = !m_Rotating;
			return false;
		}
		return false;
	}
};
