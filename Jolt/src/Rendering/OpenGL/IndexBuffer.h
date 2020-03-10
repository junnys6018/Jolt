#pragma once 
#include "glad/glad.h"
#include <cstdlib>

namespace Jolt
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(GLsizei count, const GLuint* data);

		inline GLsizei GetCount() const { return m_Count; }

		void Bind();
		void UnBind();
		~IndexBuffer();
	private:
		IndexBuffer(GLsizei count)
			:m_ID(0), m_Count(count) 
		{
	
		}
		GLuint m_ID;
		GLsizei m_Count;
	};
}