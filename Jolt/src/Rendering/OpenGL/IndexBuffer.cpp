#include "pch.h"
#include "IndexBuffer.h"

namespace Jolt
{
	IndexBuffer* IndexBuffer::Create(std::size_t count, const GLuint* data)
	{
		IndexBuffer* indexBuffer = new IndexBuffer(count);
		glGenBuffers(1, &indexBuffer->m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);

		return indexBuffer;
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
		glDeleteBuffers(1, &m_ID);
	}
}
