#include "pch.h"
#include "VertexLayout.h"

namespace Jolt
{
	VertexLayout::VertexLayout(std::initializer_list<unsigned int> AttributeLayout)
		:m_AttributeLayout(AttributeLayout.begin(), AttributeLayout.end())
	{

	}

	void VertexLayout::PushAttribute(unsigned int float_count)
	{
		m_AttributeLayout.push_back(float_count);
	}
}