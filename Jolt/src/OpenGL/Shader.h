#pragma once

#include <string>
#include <glad/glad.h>

namespace Jolt
{
	class Shader
	{
	public:
		static Shader* CreateFromFile(const std::string& shaderPath);

		void Bind();
		void UnBind();
		~Shader();
	private:
		Shader() = default;

		static GLuint CompileShader(GLenum type, const std::string& source);
	private:
		GLuint m_ID;
	};
}