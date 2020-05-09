#pragma once 
#include <glad/glad.h>

namespace Jolt
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(GLsizeiptr size, const GLvoid* data = nullptr, GLenum useage = GL_STATIC_DRAW);

		void Bind();
		void UnBind();

		inline GLuint GetHandle() { return m_ID; }

		~VertexBuffer();
	private:
		VertexBuffer()
			:m_ID(0) { }
		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;
		void Free();

		GLuint m_ID;

		friend class Mesh; // For move semantics
	};
}