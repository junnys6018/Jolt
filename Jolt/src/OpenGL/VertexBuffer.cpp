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
		glDeleteBuffers(1, &m_ID);
	}

}
