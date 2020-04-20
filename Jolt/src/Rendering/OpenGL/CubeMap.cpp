#include "pch.h"
#include "CubeMap.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <stb_image.h>

namespace Jolt
{
	CubeMap* CubeMap::Create(std::array<std::string, 6> faces)
	{
		LOG_INFO("Loading CubeMap ...");
		CubeMap* cubeMap = new CubeMap();
		glGenTextures(1, &cubeMap->m_ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap->m_ID);
		stbi_set_flip_vertically_on_load(false);
		int width, height, nrChannels;
		for (int i = 0; i < faces.size(); ++i)
		{
			LOG_INFO("\tLoading face: {}", faces[i].c_str());
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				JOLT_ASSERT(false, "Cubemap texture failed to load at path:", faces[i]);
				stbi_image_free(data);
				return nullptr;
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return cubeMap;
	}

	void CubeMap::Bind(GLuint slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

	void CubeMap::UnBind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	CubeMap::~CubeMap()
	{
		glDeleteTextures(0, &m_ID);
	}

	void DrawCubeMap(const CubeMap& cubeMap, const glm::mat4& VP)
	{
		static std::unique_ptr<VertexArray> vertex_array = CreateUnique<VertexArray>();

		static float sky_box_vertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		static std::unique_ptr<VertexBuffer> vertex_buffer = CreateUnique<VertexBuffer>(sizeof(sky_box_vertices), sky_box_vertices, GL_STATIC_DRAW);

		static const char* vertex_source = R"(
			#version 330 core

			layout(location = 0) in vec3 v_position;
			uniform mat4 VP;

			out vec3 f_TexCoord;

			void main()
			{
				f_TexCoord = v_position;
				vec4 pos = VP * vec4(v_position, 1.0);
				gl_Position = pos.xyww;
			}
		)";

		static const char* fragment_source = R"(
			#version 330 core

			in vec3 f_TexCoord;
			uniform samplerCube skybox;

			out vec4 color;

			void main()
			{
				color = texture(skybox, f_TexCoord);
			}
		)";

		static std::unique_ptr<Shader> shader = std::unique_ptr<Shader>(Shader::CreateFromChar(vertex_source, fragment_source));

		static bool first_call = true;
		if (first_call)
		{
			first_call = false;
			vertex_array->Bind();
			vertex_buffer->Bind();
			vertex_array->SetVertexLayout({ 3 });
			shader->Bind();
			shader->SetInt("skybox", 0);
		}

		glDepthFunc(GL_LEQUAL);
		cubeMap.Bind(0);
		vertex_array->Bind();
		shader->Bind();
		shader->SetMat4("VP", VP);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);
	}
}