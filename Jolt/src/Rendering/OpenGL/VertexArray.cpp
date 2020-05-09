#include "pch.h"
#include "VertexArray.h"

namespace Jolt
{
	VertexArray* VertexArray::Create()
	{
		VertexArray* vertexArray = new VertexArray();
		glGenVertexArrays(1, &vertexArray->m_ID);

		return vertexArray;
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		:m_ID(other.m_ID)
	{
		other.m_ID = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		// Check for self assignment
		if (this != &other)
		{
			Free();
			m_ID = other.m_ID;
			other.m_ID = 0;
		}
		return *this;
	}

	void VertexArray::Free()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	VertexArray::~VertexArray()
	{
		Free();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_ID);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexLayout(const VertexLayout& layout)
	{
		unsigned int stride = 0;
		for (const auto& i : layout.m_AttributeLayout)
			stride += i;

		stride *= sizeof(float);

		unsigned int offset = 0;
		for (int i = 0; i < layout.m_AttributeLayout.size(); i++ )
		{
			glVertexAttribPointer(i, layout.m_AttributeLayout[i], GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
			glEnableVertexAttribArray(i);
			offset += layout.m_AttributeLayout[i];
		}

	}
}