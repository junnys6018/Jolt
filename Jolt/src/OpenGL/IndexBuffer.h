#pragma once 
#include "glad/glad.h"
#include <cstdlib>

namespace Jolt
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(std::size_t count, const GLuint* data);

		void Bind();
		void UnBind();
		~IndexBuffer();
	private:
		IndexBuffer(std::size_t count)
			:m_ID(0), m_Count(count) 
		{
	
		}
		GLuint m_ID;
		std::size_t m_Count;
	};
}