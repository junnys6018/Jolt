#include "pch.h"
#include "VertexBuffer.h"

namespace Jolt
{

	VertexBuffer* VertexBuffer::Create(GLsizeiptr size, const GLvoid* data, GLenum useage)
	{
		VertexBuffer* vertexBuffer = new VertexBuffer();
		glGenBuffers(1, &vertexBuffer->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, useage);

		return vertexBuffer;
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		GLint current_vertex_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current_vertex_buffer);
		if (current_vertex_buffer == m_ID)
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glDeleteBuffers(1, &m_ID);
	}

}
