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

	VertexArray::~VertexArray()
	{
		GLint current_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current_vertex_array);
		if (current_vertex_array == m_ID)
		{
			glBindVertexArray(0);
		}
		glDeleteVertexArrays(1, &m_ID);
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