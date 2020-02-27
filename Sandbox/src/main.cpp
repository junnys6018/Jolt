#include "Jolt.h"


class ExampleLayer : public Jolt::Layer
{
public:
	ExampleLayer()
		:Layer()
	{

	}

	virtual void OnUpdate(float ts) override
	{
		glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");

		ImGui::ColorEdit3("Clear Color", &clearColor[0]);
		ImGui::Text("Hello World");

		ImGui::End();
	}

private:
	glm::vec3 clearColor;
};

int main()
{
	Jolt::Application app("Testing");
	app.PushLayer(new ExampleLayer());
	
	app.Run();

	return 0;
}