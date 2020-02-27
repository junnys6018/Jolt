#include "Jolt.h"
#include <iostream>

int main()
{
	Jolt::Application app("Testing");

	Jolt::ImGuiInit();

	glm::vec4 clearColor;
	while (!app.GetWindow().WindowShouldClose())
	{
		Jolt::ImGuiBeginFrame();

		ImGui::Begin("test");

		ImGui::ColorEdit4("Clear Color", &clearColor[0]);
		ImGui::Text("Hello World");

		ImGui::End();

		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

		Jolt::ImGuiEndFrame();
	}
	
	Jolt::ImGuiDestroy();


	return 0;
}