#include "pch.h"
#include "FrameBuffer.h"

namespace Jolt
{
	FrameBuffer* FrameBuffer::Create(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0)
		{
			GLint dims[4] = { 0 };
			glGetIntegerv(GL_VIEWPORT, dims);
			width = dims[2];
			height = dims[3];
		}

		// Generate and bind framebuffer
		FrameBuffer* frame_buffer = new FrameBuffer();
		glGenFramebuffers(1, &frame_buffer->m_FBOHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer->m_FBOHandle);

		// Generate and attatch texture as color buffer
		glGenTextures(1, &frame_buffer->m_ColorBuffer.m_ID);
		glBindTexture(GL_TEXTURE_2D, frame_buffer->m_ColorBuffer.m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_buffer->m_ColorBuffer.m_ID, 0);

		// Generate and attatch renderbuffer as depth/stencil buffer
		glGenRenderbuffers(1, &frame_buffer->m_RBOHandle);
		glBindRenderbuffer(GL_RENDERBUFFER, frame_buffer->m_RBOHandle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frame_buffer->m_RBOHandle);

		JOLT_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return frame_buffer;
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBOHandle);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteRenderbuffers(1, &m_RBOHandle);
		glDeleteFramebuffers(1, &m_FBOHandle);
	}
}