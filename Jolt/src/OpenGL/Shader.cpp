#include "pch.h"
#include "Shader.h"

#include <fstream>

namespace Jolt
{
	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	static ShaderSource ReadFileAsString(const std::string& filepath)
	{
		ShaderSource source;

		enum Mode
		{
			NONE = -1,
			VERTEX_SHADER = 0,
			FRAGMENT_SHADER = 1,
		};

		Mode mode = Mode::NONE;
		std::ifstream file(filepath);
		if (!file)
		{
			LOG_ERROR("Could not open file '{0}'", filepath);
		}
		std::string line;

		while (std::getline(file, line))
		{
			if (line == "#Shader Vertex")
				mode = Mode::VERTEX_SHADER;
			else if (line == "#Shader Fragment")
				mode = Mode::FRAGMENT_SHADER;
			else if (mode != Mode::NONE)
			{
				if (mode == Mode::VERTEX_SHADER)
					source.VertexSource += line + '\n';
				else
					source.FragmentSource += line + '\n';
			}

		}
		return source;
	}

	Shader* Shader::CreateFromFile(const std::string& shaderPath)
	{
		Shader* shader = new Shader();
		ShaderSource source = ReadFileAsString(shaderPath);

		GLuint program = glCreateProgram();

		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
		glAttachShader(program, vertexShader);
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			if (maxLength != 0)
			{
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
				LOG_ERROR("{0}", infoLog.data());
			}

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		shader->m_ID = program;
		return shader;
	}

	void Shader::Bind()
	{
		glUseProgram(m_ID);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ID);
	}

	GLuint Shader::CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			if (maxLength != 0)
			{
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				LOG_ERROR("{0}", infoLog.data());
			}

			glDeleteShader(shader);

		}

		return shader;
	}

	// Uniform Setting
	GLint Shader::GetUniformLocation(const std::string& name) const
	{
		glUseProgram(m_ID);
		if (m_UniformLocations.find(name) != m_UniformLocations.end())
			return m_UniformLocations[name];

		GLint location = glGetUniformLocation(m_ID, name.c_str());
		if (location == -1)
			std::cout << name << " is not a valid uniform\n";
		m_UniformLocations[name] = location;
		return location;
	}

	// setter methods for shader uniforms
	void Shader::SetInt(const std::string & name, const int& value) const
	{
		GLint location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void Shader::SetBool(const std::string & name, const bool& value) const
	{
		SetInt(name, (int)value);
	}

	void Shader::SetMat4(const std::string & name, const glm::mat4 & mat) const
	{

		GLint location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetVec3(const std::string & name, const float& x, const float& y, const float& z) const
	{
		GLint location = GetUniformLocation(name);
		glUniform3f(location, x, y, z);
	}

	void Shader::SetVec3(const std::string & name, const glm::vec3 & value) const
	{
		SetVec3(name, value.x, value.y, value.z);
	}

	void Shader::SetVec2(const std::string & name, const float& x, const float& y) const
	{
		GLint location = GetUniformLocation(name);
		glUniform2f(location, x, y);
	}

	void Shader::SetVec2(const std::string & name, const glm::vec2 & value) const
	{
		SetVec2(name, value.x, value.y);
	}

	void Shader::SetFloat(const std::string & name, const float& value) const
	{
		GLint location = GetUniformLocation(name);
		glUniform1f(location, value);
	}
}