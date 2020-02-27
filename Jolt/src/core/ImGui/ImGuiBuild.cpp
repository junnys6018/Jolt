#include "pch.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "examples/imgui_impl_opengl3.cpp"
#include "examples/imgui_impl_glfw.cpp"

#include "ImGuiBuild.h"
#include "Application.h"

namespace Jolt
{
	void ImGuiInit()
	{
		// Create window with graphics context
		auto window = Application::Get().GetWindow();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window.GetNaitiveWindow(), true);
		ImGui_ImplOpenGL3_Init();
	}

	void ImGuiBeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiEndFrame()
	{
		auto window = Application::Get().GetWindow();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize((GLFWwindow*)window.GetNaitiveWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiDestroy()
	{
		auto window = Application::Get().GetWindow();

		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow((GLFWwindow*)window.GetNaitiveWindow());
		glfwTerminate();
	}
}