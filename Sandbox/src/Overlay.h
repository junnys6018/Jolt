#pragma once
#include "Jolt.h"
#include "Example1.h"
#include "Example2.h"

using namespace Jolt;

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer()
		:Layer("ExampleOverlay"), m_State(State::None), m_CurrentLayer(nullptr)
	{

	}

	virtual void OnImGuiRender() override
	{
		JOLT_PROFILE_FUNCTION();

		ImGui::Begin("test");
		switch (m_State)
		{
		case State::None:
			if (ImGui::Button("Example 1"))
			{
				m_CurrentLayer = new ExampleLayer();
				Application::Get().PushLayer(m_CurrentLayer);
				m_State = State::Example1;
			}

			if (ImGui::Button("Example 2"))
			{
				m_CurrentLayer = new ExampleLayer2();
				Application::Get().PushLayer(m_CurrentLayer);
				m_State = State::Example2;
			}
			break;
		case State::Example1:
		case State::Example2:
			if (ImGui::Button("<-"))
			{
				Application::Get().PopLayer(m_CurrentLayer);
				m_CurrentLayer = nullptr;
				m_State = State::None;
			}
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

	Layer* m_CurrentLayer;
};