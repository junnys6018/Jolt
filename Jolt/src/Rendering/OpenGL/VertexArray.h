#pragma once
#include <glad/glad.h>

#include "VertexLayout.h"

namespace Jolt
{
	class VertexArray
	{
	public:
		static VertexArray* Create();
		~VertexArray();

		void Bind();
		void UnBind();

		inline GLuint GetHandle() { return m_ID; }

		void SetVertexLayout(const VertexLayout& layout);
	private:
		VertexArray()
			:m_ID(0) {}
		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;
		void Free();
		
		GLuint m_ID;

		friend class Mesh; // For move semantics
	};
}