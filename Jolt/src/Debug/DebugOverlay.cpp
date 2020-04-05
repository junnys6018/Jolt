#include "pch.h"
#include "DebugOverlay.h"
#include "Core/Application.h"
#include "Profiling/Timer.h"
#include "Core/Ticker.h"
#include <imgui.h>

namespace Jolt
{
	DebugOverlay::DebugOverlay()
		:Layer("DebugOverlay"), m_Open(true), m_Selected(nullptr)
	{

	}

	void DebugOverlay::OnAttach()
	{
		m_Selected = Application::Get().m_LayerStack.m_Layers[0];
	}

	void DebugOverlay::OnImGuiRender()
	{
		JOLT_PROFILE_FUNCTION();
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
			static float time = 30.0f;
			if (ImGui::BeginChild("LayerInfo", ImVec2(0.0f, -ImGui::GetFrameHeightWithSpacing())))
			{
				ImGui::Text(m_Selected->GetName().c_str());
				ImGui::Separator();
#ifdef JOLT_PROFILE
				if (ImGui::Button("Profile Layer"))
				{
					LOG_INFO("Profiled {} ms!", time);
					CPUProfiler::Get().BeginInstrumentation((int)std::hash<void*>{}((void*)m_Selected), (long long)(time * 1000.0f));
				}
				ImGui::SameLine();
				if (ImGui::Button("Profile Application"))
				{
					LOG_INFO("Profiled {} ms!", time);
					CPUProfiler::Get().BeginInstrumentation(0, (long long)(time * 1000.0f));
				}
				ImGui::SameLine();
				ImGui::PushItemWidth(80.0f);
				ImGui::DragFloat("##Time", &time, 5.0f, 30.0f, 1000.0f, "%.0f ms");
				ImGui::PopItemWidth();

				DrawProfileData((int)std::hash<void*>{}((void*)m_Selected));
#endif
			}
			ImGui::EndChild();

			ImGui::Text("FPS: %.1f (%.3f ms/frame)", Application::Get().GetFPS(), 1000.0f / Application::Get().GetFPS());

			ImGui::EndGroup();
			
			ImGui::End();
			if (show_demo_menu)
				ImGui::ShowDemoWindow(&show_demo_menu);
		}
		else
		{
#ifdef JOLT_PROFILE
			CPUProfiler::Get().Clear();
#endif
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

	void DebugOverlay::DrawProfileData(int id)
	{
		JOLT_PROFILE_FUNCTION();
		static std::map<int, std::vector<ProfileData>> cached_profile_results = CPUProfiler::Get().GetProfileResults();
		static Ticker ticker(400.0f); // Update every 400ms
		if (ticker.IsReady())
		{
			ticker.Reset();
			cached_profile_results = CPUProfiler::Get().GetProfileResults();
		}
		auto& profile_data = cached_profile_results[id];
		ImGui::Columns(2, "mycol");
		float width = ImGui::GetWindowContentRegionWidth();
		ImGui::SetColumnWidth(0, width - 80.0f);
		ImGui::Separator();
		ImGui::Text("Name"); ImGui::NextColumn();
		ImGui::Text("Time (ms)"); ImGui::NextColumn();
		ImGui::Separator();

		float total = 0.0f;
		for (const ProfileData& duration : profile_data)
		{
			float ms_time = (duration.end - duration.start) * 0.001f;
			total += ms_time;
			ImGui::Text(duration.name);
			ImGui::NextColumn();
			ImGui::Text("%.3f", ms_time);
			ImGui::NextColumn();
		}
		ImGui::Separator();
		ImGui::Text("Total time");
		ImGui::NextColumn();
		ImGui::Text("%.3f", total);
		ImGui::NextColumn();
		ImGui::Columns(1);
		ImGui::Separator();

		CPUProfiler::Get().Clear(); // Clear here for now
	}
}
