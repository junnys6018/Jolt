#pragma once
#include "Jolt.h"

using namespace Jolt;

class ExampleLayer2 : public Layer
{
public:
	using GoochRenderer = Jolt::Renderer<LightPoint, MatGooch>;
	using FlatColorRenderer = Jolt::Renderer<LightDummy, MatDummy>;
	ExampleLayer2()
		:Layer("Example 2"), m_ClearColor(0.0f), 
		m_Model(CreateFromFile("data"), 
		{
			MaterialMapper<MatGooch>(std::shared_ptr<MatGooch>(new MatGooch(glm::vec3(0.980f, 0.439f, 0.780f))),
			0, (CreateFromFile("data").m_IndexBuffer->GetCount() / 6) * 3), 
			MaterialMapper<MatGooch>(std::shared_ptr<MatGooch>(new MatGooch(glm::vec3(0.0f, 0.921f, 0.117f))), 
			(CreateFromFile("data").m_IndexBuffer->GetCount() / 6) * 3, CreateFromFile("data").m_IndexBuffer->GetCount())
		}),
		m_Cube(CuboidBuilder(0.1f).GenerateMesh()),
		m_Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f)), m_Rotating(false), m_Angle(0.0f), m_RotateSpeed(1.0f)
	{
	
	}

	virtual void OnAttach() override
	{
		glEnable(GL_DEPTH_TEST);

		m_GoochShader = std::unique_ptr<Shader>(Shader::CreateFromFile("Gooch.glsl"));
		m_FlatColorShader = std::unique_ptr<Shader>(Shader::CreateFromFile("FlatColor.glsl"));
		m_FlatColorShader->Bind();
		m_FlatColorShader->SetVec3("u_Color", 1.0f, 1.0f, 1.0f);
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
		model = glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(1.0f, 1.0, 0.0f));

		m_Model.SetTransform(model);

		glm::vec3 lightpos = glm::vec3(sinf((float)glfwGetTime()), 0.0f, cosf((float)glfwGetTime()));

		{
			JOLT_PROFILE_SCOPE("Renderer::Draw");
			GoochRenderer::BeginScene(LightPoint(glm::vec3(1.0f), lightpos), m_GoochShader.get(), m_Camera.GetCamera());
			GoochRenderer::Submit(m_Model);
			GoochRenderer::EndScene();

			FlatColorRenderer::BeginScene(m_FlatColorShader.get(), m_Camera.GetCamera());
			m_Cube.SetTransform(glm::translate(glm::mat4(1.0f), lightpos));
			FlatColorRenderer::Submit(m_Cube);
			FlatColorRenderer::EndScene();
		}
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
	std::unique_ptr<Shader> m_GoochShader, m_FlatColorShader;
	DrawData<MatGooch> m_Model;
	DrawData<MatDummy> m_Cube;
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
