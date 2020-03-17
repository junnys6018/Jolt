#include "pch.h"
#include "ImGuiOverlay.h"

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

#include "Core/Application.h"

namespace Jolt
{
	ImGuiOverlay::ImGuiOverlay()
		:Layer("ImGuiOverlay")
	{

	}

	void ImGuiOverlay::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
		auto window = Application::Get().GetWindow();
		ImGui_ImplGlfw_InitForOpenGL(window->GetNaitiveWindow(), true);
		ImGui_ImplOpenGL3_Init();
	}

	void ImGuiOverlay::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiOverlay::OnEvent(Event* e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<MouseButtonPressedEvent>(JOLT_BIND_EVENT_FN(ImGuiOverlay::OnMouseButtonPressedEvent));
	}

	void ImGuiOverlay::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiOverlay::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	bool ImGuiOverlay::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO io = ImGui::GetIO();
		return io.WantCaptureMouse;
	}
}