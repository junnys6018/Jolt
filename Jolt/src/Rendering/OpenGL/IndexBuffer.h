#pragma once 
#include <glad/glad.h>

namespace Jolt
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(GLsizei count, const GLuint* data);

		inline GLsizei GetCount() const { return m_Count; }
		inline GLuint GetHandle() { return m_ID; }

		void Bind();
		void UnBind();

		~IndexBuffer();
	private:
		IndexBuffer(GLsizei count = 0)
			:m_ID(0), m_Count(count) 
		{
	
		}
		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;
		void Free();

		GLuint m_ID;
		GLsizei m_Count;

		friend class Mesh; // For move constructor
	};
}