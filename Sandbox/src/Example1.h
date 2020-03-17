#pragma once
#include "Jolt.h"

using namespace Jolt;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		:Layer("Example 1"), m_ClearColor(0.0f), m_VertexColor(1.0f, 0.0f, 0.0f), m_UseTexture(false)
	{

	}

	virtual void OnAttach() override
	{
		float buffer[] = {
			 -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
			  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
			  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
			 -0.5f,  0.5f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		m_VertexArray = CreateUnique<VertexArray>();
		m_VertexArray->Bind();

		m_VertexBuffer = CreateUnique<VertexBuffer>(sizeof(buffer), buffer, GL_DYNAMIC_DRAW);
		m_VertexBuffer->Bind();

		m_VertexArray->SetVertexLayout(VertexLayout({ 2,3,2 }));

		m_IndexBuffer = CreateUnique<IndexBuffer>(6, indices);
		m_IndexBuffer->Bind();

		m_Texture = CreateUnique<Texture>("HelloWorld.png");
		m_Texture->Bind();

		m_Shader = std::unique_ptr<Shader>(Shader::CreateFromFile("FlatColor.glsl"));
		m_Shader->Bind();
		m_Shader->SetBool("u_UseTexture", m_UseTexture);
		m_Shader->SetInt("u_Texture", 0);
	}

	virtual void OnDetach() override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	virtual void OnUpdate(float ts) override
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f);

		m_VertexArray->Bind();
		m_Shader->Bind();

		float* vBuf = (float*)glMapNamedBuffer(m_VertexBuffer->GetHandle(), GL_READ_WRITE);
		memcpy(vBuf + 2, &m_VertexColor[0], 3 * sizeof(float));
		glUnmapNamedBuffer(m_VertexBuffer->GetHandle());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");

		ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]);
		ImGui::ColorEdit3("Vertex Color", &m_VertexColor[0]);
		if (ImGui::Checkbox("Use Texture", &m_UseTexture))
		{
			m_Shader->SetBool("u_UseTexture", m_UseTexture);
		}

		ImGui::End();
	}

private:
	glm::vec3 m_ClearColor, m_VertexColor;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;
	bool m_UseTexture;
};