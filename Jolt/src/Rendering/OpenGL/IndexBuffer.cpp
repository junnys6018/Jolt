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

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		GLint current_index_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &current_index_buffer);
		if (current_index_buffer == m_ID)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		glDeleteBuffers(1, &m_ID);
	}
}
