#pragma once
#include <glad/glad.h>
#include "Texture.h"

namespace Jolt
{
	class FrameBuffer
	{
	public:
		// If width and height are specified to 0, the framebuffer will se set to the windows dimensions
		static FrameBuffer* Create(uint32_t width = 0, uint32_t height = 0);

		void Bind();
		void UnBind();

		inline Texture2D& GetColorAttatchment()
		{
			return m_ColorBuffer;
		}

		~FrameBuffer();
	private:
		FrameBuffer() = default;
		GLuint m_FBOHandle = 0;
		GLuint m_RBOHandle = 0;
		Texture2D m_ColorBuffer;
	};

}