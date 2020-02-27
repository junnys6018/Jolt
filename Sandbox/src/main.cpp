#include "Jolt.h"


class ExampleLayer : public Jolt::Layer
{
public:
	ExampleLayer()
		:Layer(), m_ClearColor(0.0f), m_FlatColor(2.0f)
	{

	}

	virtual void OnAttach() override
	{
		float buffer[] = {
			 -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
			  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
			  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
			 -0.5f,  0.5f,		0.5f, 0.5f, 0.5f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3
		};


		m_VertexArray = std::unique_ptr<Jolt::VertexArray>(Jolt::VertexArray::Create());
		m_VertexArray->Bind();

		m_VertexBuffer = std::unique_ptr<Jolt::VertexBuffer>(Jolt::VertexBuffer::Create(sizeof(buffer), buffer));
		m_VertexBuffer->Bind();
		
		m_VertexArray->SetVertexLayout(Jolt::VertexLayout({ 2,3 }));

		m_IndexBuffer = std::unique_ptr<Jolt::IndexBuffer>(Jolt::IndexBuffer::Create(6, indices));
		m_IndexBuffer->Bind();

		m_Shader = std::unique_ptr<Jolt::Shader>(Jolt::Shader::CreateFromFile("FlatColor.glsl"));
	}

	virtual void OnDetach() override 
	{

	}

	virtual void OnUpdate(float ts) override
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_VertexArray->Bind();
		m_Shader->Bind();
		//m_Shader->SetVec3("u_FlatColor", m_FlatColor);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");

		ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]);
		ImGui::ColorEdit3("Flat Color", &m_FlatColor[0]);

		ImGui::End();
	}

private:
	glm::vec3 m_ClearColor, m_FlatColor;
	std::unique_ptr<Jolt::VertexBuffer> m_VertexBuffer;
	std::unique_ptr<Jolt::IndexBuffer> m_IndexBuffer;
	std::unique_ptr<Jolt::VertexArray> m_VertexArray;
	std::unique_ptr<Jolt::Shader> m_Shader;
};

int main()
{
	Jolt::Application app("Testing");
	app.PushLayer(new ExampleLayer());
	
	app.Run();

	return 0;
}