#pragma once
#include "pch.h"
#include <glad/glad.h>

namespace Jolt
{
	class Texture2D
	{
	public:
		static Texture2D* Create(const std::string& filepath);
		static Texture2D* Create(float r, float g, float b);

		void Bind(GLuint slot = 0);
		// void UnBind();
		inline GLuint GetHandle() { return m_ID; }

		~Texture2D();
	private:
		Texture2D()
			:m_ID(0)
		{

		}
		GLuint m_ID;

		// Framebuffer needs access to constructor as it "owns" its attached texture
		friend class FrameBuffer;
	};
}