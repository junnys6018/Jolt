#pragma once
#include "glad/glad.h"

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

		void SetVertexLayout(const VertexLayout& layout);
	private:
		VertexArray() = default;
		GLuint m_ID;
	};
}