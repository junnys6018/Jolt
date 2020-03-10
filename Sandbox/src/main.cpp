#include "Jolt.h"
using namespace Jolt;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		:Layer(), m_ClearColor(0.0f), m_Rotating(false), m_Angle(0.0f), m_RotateSpeed(1.0f)
	{

	}

	virtual void OnAttach() override
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		EllipsoidBuilder builder(5.0f, 3.0f, 3.0f, 64U);
		//CuboidBuilder builder(2.0f);

		m_Mesh = builder.GenerateMesh();
		m_CubeShader = std::unique_ptr<Shader>(Shader::CreateFromFile("Cube.glsl"));
	}

	virtual void OnDetach() override 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	virtual void OnUpdate(float ts) override
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f);

		if (m_Rotating)
		{
			m_Angle += ts * m_RotateSpeed;
		}

		int width, height;
		glfwGetFramebufferSize(Application::Get().GetWindow()->GetNaitiveWindow(), &width, &height);
		float aspect = (float)width / height;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));
		model = glm::rotate(model, m_Angle, glm::vec3(1.0f, 1.0, 0.0f));

		glm::mat4 proj = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
		m_CubeShader->SetMat4("u_MVP", proj * model);
		m_Mesh.VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_Mesh.IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");

		if (ImGui::Button("<-"))
		{
			Application::Get().PopLayer(this);
		}
		ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]);
		ImGui::SliderFloat("Rotate Speed", &m_RotateSpeed, 0.1f, 5.0f);
		ImGui::Text("Press 'A' to Rotate.   FPS: %.1f", Application::Get().GetFPS());

		ImGui::End();
	}

	virtual void OnEvent(Event* e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(JOLT_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

private:
	glm::vec3 m_ClearColor;
	std::unique_ptr<Shader> m_CubeShader;
	Mesh m_Mesh;

	bool m_Rotating;
	float m_Angle, m_RotateSpeed;
	
private:
	bool OnKeyPressedEvent(KeyPressedEvent e)
	{
		if (e.GetKeyCode() == JOLT_KEY_A)
		{
			m_Rotating = !m_Rotating;
			return false;
		}
		return false;
	}
};

class ExampleLayer2 : public Layer
{
public:
	ExampleLayer2()
		:Layer(), m_ClearColor(0.0f), m_VertexColor(1.0f, 0.0f, 0.0f)
	{

	}

	virtual void OnAttach() override
	{
		float buffer[] = {
			 -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
			  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
			  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
			 -0.5f,  0.5f,		0.0f, 1.0f, 1.0f
		};

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		m_VertexArray = CreateUnique<VertexArray>();
		m_VertexArray->Bind();

		m_VertexBuffer = CreateUnique<VertexBuffer>(sizeof(buffer), buffer, GL_DYNAMIC_DRAW);
		m_VertexBuffer->Bind();

		m_VertexArray->SetVertexLayout(VertexLayout({ 2,3 }));

		m_IndexBuffer = CreateUnique<IndexBuffer>(6, indices);
		m_IndexBuffer->Bind();

		m_Shader = std::unique_ptr<Shader>(Shader::CreateFromFile("FlatColor.glsl"));
	}

	virtual void OnDetach() override
	{

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

		if (ImGui::Button("<-"))
		{
			Application::Get().PopLayer(this);
		}
		ImGui::ColorEdit3("Clear Color", &m_ClearColor[0]);
		ImGui::ColorEdit3("Vertex Color", &m_VertexColor[0]);
		ImGui::Text("FPS: %.1f", Application::Get().GetFPS());

		ImGui::End();
	}

private:
	glm::vec3 m_ClearColor, m_VertexColor;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<Shader> m_Shader;
};

class ImGuiOverlay : public Layer
{
public:
	ImGuiOverlay()
		:Layer(), m_State(State::None)
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");
		switch (m_State)
		{
		case State::None:
			if (ImGui::Button("1"))
			{
				Application::Get().PushLayer(new ExampleLayer());
			}
			
			if (ImGui::Button("2"))
			{
				Application::Get().PushLayer(new ExampleLayer2());
			}
			break;
		case State::Example1:
			break;
		case State::Example2:
			break;
		}


		ImGui::End();
	}

private:
	enum class State
	{
		None,
		Example1,
		Example2
	} m_State;
};

class ExampleApp : public Application
{
public:
	ExampleApp()
		:Application("Sandbox")
	{
		PushOverlay(new ImGuiOverlay());
		//PushLayer(new ExampleLayer());
		//PushLayer(new ExampleLayer2());
	}
};

int main()
{
	ExampleApp* app = new ExampleApp();
	app->Run();

	return 0;
}