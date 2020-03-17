#pragma once
#include "Core/Layer.h"
#include "Core/Events/MouseEvent.h"

namespace Jolt
{
	class ImGuiOverlay : public Layer
	{
	public:
		ImGuiOverlay();
		~ImGuiOverlay() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(Event* e) override;

		void Begin();
		void End();

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	};
}