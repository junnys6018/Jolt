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
		CuboidBuilder builder(1.0f, 1.0f, 2.0f);
		m_Mesh = builder.GenerateMesh();
		m_CubeShader = std::unique_ptr<Shader>(Shader::CreateFromFile("Cube.glsl"));
	}

	virtual void OnDetach() override 
	{

	}

	virtual void OnUpdate(float ts) override
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");

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
			return true;
		}
		return false;
	}
};

int main()
{
	Application app("Testing");
	app.PushLayer(new ExampleLayer());
	
	app.Run();

	return 0;
}