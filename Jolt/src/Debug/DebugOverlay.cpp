#include "pch.h"
#include "DebugOverlay.h"
#include "Core/Application.h"

#include <imgui.h>

namespace Jolt
{
	DebugOverlay::DebugOverlay()
		:Layer("DebugOverlay"), m_Open(false), m_Selected(nullptr)
	{

	}

	void DebugOverlay::OnAttach()
	{
		m_Selected = Application::Get().m_LayerStack.m_Layers[0];
	}

	void DebugOverlay::OnImGuiRender()
	{
		if (m_Open)
		{
			ImGui::Begin("Debug", &m_Open, ImGuiWindowFlags_MenuBar);
			static bool show_demo_menu = false;
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Menu"))
				{
					ImGui::Checkbox("Demo", &show_demo_menu);
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ImGui::BeginGroup();
			ImGui::Text("Layer Stack");

			auto& layer_stack = Application::Get().m_LayerStack.m_Layers;
			if (ImGui::BeginChild("Layers", ImVec2(150.0f, 0.0f), true))
			{
				for (int i = 0; i < layer_stack.size(); i++)
				{
					auto& layer = layer_stack[i];
					ImGui::Text("%i.", i + 1);
					ImGui::SameLine();
					if (ImGui::Selectable(layer->GetName().c_str(), m_Selected == layer))
						m_Selected = layer;
				}
			}
			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::SameLine();
			
			ImGui::BeginGroup();

			if (ImGui::BeginChild("LayerInfo", ImVec2(0.0f, -ImGui::GetFrameHeightWithSpacing())))
			{
				ImGui::Text(m_Selected->GetName().c_str());
				ImGui::Separator();
			}
			ImGui::EndChild();

			ImGui::Text("FPS: %.1f (%.3f ms/frame)", Application::Get().GetFPS(), 1000.0f / Application::Get().GetFPS());

			ImGui::EndGroup();
			
			ImGui::End();
			if (show_demo_menu)
				ImGui::ShowDemoWindow(&show_demo_menu);
		}
	}

	void DebugOverlay::OnEvent(Event* e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<KeyPressedEvent>(JOLT_BIND_EVENT_FN(DebugOverlay::OnKeyPressedEvent));
		dispatch.Dispatch<EngineLayerPoppedEvent>([this](EngineLayerPoppedEvent e) -> bool
		{
			if (e.GetLayer() == m_Selected)
				m_Selected = Application::Get().m_LayerStack.m_Layers[0];

			return false;
		});

		dispatch.Dispatch<EngineOverlayPoppedEvent>([this](EngineOverlayPoppedEvent e) -> bool
		{
			if (e.GetLayer() == m_Selected)
				m_Selected = Application::Get().m_LayerStack.m_Layers[0];

			return false; 
		});
	}

	bool DebugOverlay::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == JOLT_KEY_F1)
		{
			m_Open = !m_Open;
			return true;
		}
		return false;
	}
}
