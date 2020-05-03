#pragma once
#include "Jolt.h"

using namespace Jolt;

class ExampleLayer3 : public Layer
{
public:
	ExampleLayer3()
		:Layer("Example 3"), m_ClearColor(0.0f), m_Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f))
	{

	}

	virtual void OnAttach() override
	{
		MeshMetaData mesh_meta_data;
		Mesh mesh = CreateFromFile("res/sp.jltmsh", &mesh_meta_data);

		m_Model = std::make_unique<DrawData<MatGooch>>(std::move(mesh), std::make_shared<MatGooch>(glm::vec3(0.090f, 0.992f, 0.941f)));

		m_GoochShader = CreateUnique<Shader>("res/Gooch.glsl", mesh_meta_data.GetReplacementMap());

		RectangleBuilder builder{};
		builder.SetMeshProps(MeshPropsTextureCoords);
		m_FlatRectangle = builder.GenerateMesh();

		m_RenderTarget = CreateUnique<FrameBuffer>();
		m_RenderTarget->GetColorAttatchment().Bind();

		m_PostProcessShader = CreateUnique<Shader>("src/Example3/PostProcess.glsl");
		m_PostProcessShader->Bind();
		m_PostProcessShader->SetInt("u_Texture", 0);
	}

	virtual void OnDetach() override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glDisable(GL_DEPTH_TEST);
	}

	virtual void OnUpdate(float ts) override
	{
		JOLT_PROFILE_FUNCTION();
		m_Camera.OnUpdate(ts);

		m_RenderTarget->Bind();

		glEnable(GL_DEPTH_TEST);
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		GoochRenderer::BeginScene(LightPoint(glm::vec3(1.0f), glm::vec3(0.0f, 2.0f, 0.0f)), m_GoochShader.get(), m_Camera.GetCamera());
		GoochRenderer::Submit(*m_Model);
		GoochRenderer::EndScene();

		m_RenderTarget->UnBind();

		m_FlatRectangle.m_VertexArray->Bind();
		m_PostProcessShader->Bind();
		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual void OnImGuiRender() override
	{
		JOLT_PROFILE_FUNCTION();
		ImGui::Begin("test");

		ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]);

		ImGui::End();
	}

	virtual void OnEvent(Event* e) override
	{
		m_Camera.OnEvent(e);
	}

private:
	glm::vec3 m_ClearColor;
	CameraController m_Camera;
	std::unique_ptr<DrawData<MatGooch>> m_Model;
	std::unique_ptr<Shader> m_GoochShader, m_PostProcessShader;
	Mesh m_FlatRectangle;
	std::unique_ptr<FrameBuffer> m_RenderTarget;
};