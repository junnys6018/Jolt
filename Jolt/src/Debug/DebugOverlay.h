#pragma once
#include "Core/Layer.h"
#include "Core/Events/__Events__.h"

namespace Jolt
{
	class DebugOverlay : public Layer
	{
	public:
		DebugOverlay();
		~DebugOverlay() = default;

		virtual void OnAttach() override;
		//virtual void OnDetach() override;
		//virtual void OnUpdate(float ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event* e) override;

	private:
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		void DrawProfileData(int id);

	private:
		bool m_Open;
		Layer* m_Selected;
		void* m_ApplicationPtr;
	};
}