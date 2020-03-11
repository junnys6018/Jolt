#pragma once
#include "pch.h"
#include <glad/glad.h>

namespace Jolt
{
	class Texture
	{
	public:
		static Texture* Create(const std::string& filepath);
		static Texture* Create(float r, float g, float b);

		void Bind(unsigned int slot = 0);
		// void UnBind();
		inline GLuint GetHandle() { return m_ID; }

		~Texture();
	private:
		Texture()
			:m_ID(0)
		{

		}
		GLuint m_ID;
	};
}