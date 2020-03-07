#pragma once 
#include "glad/glad.h"

namespace Jolt
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(GLsizeiptr size, const GLvoid* data = nullptr, GLenum useage = GL_STATIC_DRAW);

		void Bind();
		void UnBind();
		~VertexBuffer();
	private:
		VertexBuffer() = default;
		GLuint m_ID;
	};
}