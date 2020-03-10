#include "pch.h"
#include "LayerStack.h"

namespace Jolt {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace(m_Layers.begin() + m_OverlayInsertIndex, overlay);
		m_OverlayInsertIndex++;
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin() + m_OverlayInsertIndex, m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
		}
		delete layer;
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_OverlayInsertIndex, overlay);
		if (it != m_Layers.begin() + m_OverlayInsertIndex)
		{
			overlay->OnDetach();
			m_Layers.erase(it);
			m_OverlayInsertIndex--;
		}
		delete overlay;
	}
}
