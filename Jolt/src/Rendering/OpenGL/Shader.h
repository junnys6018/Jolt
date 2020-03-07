#pragma once
#include <string>
#include <map>


#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Jolt
{
	class Shader
	{
	public:
		static Shader* CreateFromFile(const std::string& shaderPath);

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
		~Shader();
	private:
		Shader() = default;

		static GLuint CompileShader(GLenum type, const std::string& source);
		GLint GetUniformLocation(const std::string& name) const;
	private:
		GLuint m_ID;
		mutable std::map<std::string, GLint> m_UniformLocations;
	};
}