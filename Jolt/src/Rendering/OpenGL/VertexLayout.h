#pragma once

#include <vector>
#include <initializer_list>

namespace Jolt
{
	// Assumes interleaved float data
	class VertexLayout
	{
	public:
		VertexLayout(std::initializer_list<unsigned int> AttributeLayout);

		void PushAttribute(unsigned int float_count);

		friend class VertexArray;
	private:
		std::vector<unsigned int> m_AttributeLayout;
	};
}