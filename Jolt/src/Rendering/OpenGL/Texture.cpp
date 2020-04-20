#include "pch.h"
#include "Texture.h"

#include <stb_image.h>

namespace Jolt
{
	Texture* Texture::Create(const std::string& filepath)
	{
		LOG_INFO("Loading Texture: {}", filepath);
		Texture* texture = new Texture();
		glGenTextures(1, &texture->m_ID);
		glBindTexture(GL_TEXTURE_2D, texture->m_ID);

		// set the ID wrapping/filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			GLint format;
			switch (channels)
			{
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				JOLT_ASSERT(false, "Channel Format not supported");
				break;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			const char* log = stbi_failure_reason();
			JOLT_ASSERT(false, "Failed to load:", filepath, log);
		}

		stbi_image_free(data);
		return texture;
	}

	Texture* Texture::Create(float r, float g, float b)
	{
		Texture* texture = new Texture();
		glGenTextures(1, &texture->m_ID);
		glBindTexture(GL_TEXTURE_2D, texture->m_ID);

		// set the ID wrapping/filtering options (on the currently bound ID object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		JOLT_ASSERT(r <= 1.0f && r >= 0.0f && g <= 1.0f && g >= 0.0f && b <= 1.0f && b >= 0.0f, "Color not in range");
		float data[] = { r,g,b };

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, data);

		return texture;
	}

	void Texture::Bind(GLuint slot)
	{
		glBindTextureUnit(slot, m_ID);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}
}