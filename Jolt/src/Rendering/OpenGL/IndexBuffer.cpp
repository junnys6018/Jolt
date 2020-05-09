#include "pch.h"
#include "IndexBuffer.h"

namespace Jolt
{
	IndexBuffer* IndexBuffer::Create(GLsizei count, const GLuint* data)
	{
		IndexBuffer* index_buffer = new IndexBuffer(count);
		glGenBuffers(1, &index_buffer->m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);

		return index_buffer;
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
		:m_ID(other.m_ID), m_Count(other.m_Count)
	{
		other.m_ID = 0;
		other.m_Count = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		// Check for self assignment
		if (this != &other)
		{
			Free();
			m_ID = other.m_ID;
			m_Count = other.m_Count;

			other.m_ID = 0;
			other.m_Count = 0;
		}
		return *this;
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Free()
	{
		glDeleteBuffers(1, &m_ID);
	}

	IndexBuffer::~IndexBuffer()
	{
		Free();
	}
}
