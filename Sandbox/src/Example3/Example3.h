#pragma once
#include "Jolt.h"

using namespace Jolt;

class ExampleLayer3 : public Layer
{
public:
	ExampleLayer3()
		:Layer("Example 3"), m_Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f)), m_PostProcess(false)
	{

	}

	virtual void OnAttach() override
	{
		m_Camera.SetSpeed(0.005f);

		MeshMetaData mesh_meta_data;
		Mesh mesh = CreateFromFile("res/sp.jltmsh", &mesh_meta_data);

		m_Model = std::make_unique<DrawData<MatGooch>>(std::move(mesh), std::make_shared<MatGooch>(glm::vec3(0.090f, 0.992f, 0.941f)));

		m_GoochShader = CreateUnique<Shader>("res/Gooch.glsl", mesh_meta_data.GetReplacementMap());

		m_PostProcessShader = CreateUnique<Shader>("src/Example3/PostProcess.glsl");
		m_PostProcessShader->Bind();
		m_PostProcessShader->SetInt("u_Texture", 0);

		m_RenderTarget = CreateUnique<FrameBuffer>();
		m_RenderTarget->GetColorAttatchment().Bind();

		RectangleBuilder builder{};
		builder.SetMeshProps(MeshPropsTextureCoords);
		m_FlatRectangle = builder.GenerateMesh();
	}

	virtual void OnDetach() override
	{
		glDisable(GL_DEPTH_TEST);
	}

	virtual void OnUpdate(float ts) override
	{
		JOLT_PROFILE_FUNCTION();
		m_Camera.OnUpdate(ts);

		m_RenderTarget->Bind();

		glEnable(GL_DEPTH_TEST);
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
		if (ImGui::Checkbox("Post Processing", &m_PostProcess))
		{
			m_PostProcessShader->SetBool("u_PostProcess", m_PostProcess);
		}
		ImGui::End();
	}

	virtual void OnEvent(Event* e) override
	{
		m_Camera.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent & e) -> bool {
			this->m_RenderTarget = CreateUnique<FrameBuffer>(e.GetWidth(), e.GetHeight());
			this->m_RenderTarget->GetColorAttatchment().Bind();
			//LOG_INFO("FB Resize: width:{} height:{}", e.GetWidth(), e.GetHeight());
			return false;
		});
	}

private:
	CameraController m_Camera;
	bool m_PostProcess;
	std::unique_ptr<DrawData<MatGooch>> m_Model;
	std::unique_ptr<Shader> m_GoochShader, m_PostProcessShader;
	std::unique_ptr<FrameBuffer> m_RenderTarget;
	Mesh m_FlatRectangle;
};