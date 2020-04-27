#pragma once
#include <string>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Jolt
{
	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		static Shader* Create(const std::string& shaderPath, std::map<std::string, std::string> replacements = std::map<std::string, std::string>());
		static Shader* Create(const char* vertexSrc, const char* fragmentSrc, std::map<std::string, std::string> replacements = std::map<std::string, std::string>());

		// Functions sets Uniforms in the shader code
		void SetInt(const std::string& name, const int& value) const;
		void SetBool(const std::string& name, const bool& value) const;
		void SetMat4(const std::string& name, const glm::mat4& mat) const;
		void SetVec3(const std::string& name, const float& x, const float& y, const float& z) const;
		void SetVec3(const std::string& name, const glm::vec3& value) const;
		void SetVec2(const std::string& name, const float& x, const float& y) const;
		void SetVec2(const std::string& name, const glm::vec2& value) const;
		void SetFloat(const std::string& name, const float& value) const;

		void Bind();
		void UnBind();

		inline GLuint GetHandle() { return m_ID; }

		~Shader();
	private:
		Shader() = default;

		static void PreprocessShader(std::string& source, std::map<std::string, std::string> replacements);
		static GLuint CompileShader(GLenum type, const std::string& source);
		static GLuint CreateProgram(Shader* shader, ShaderSource& source, std::map<std::string, std::string> replacements);
		GLint GetUniformLocation(const std::string& name) const;
	private:
		GLuint m_ID = 0;
		mutable std::map<std::string, GLint> m_UniformLocations;
	};
}