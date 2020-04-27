#include "pch.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

namespace Jolt
{
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

	Shader* Shader::Create(const std::string& shaderPath, std::map<std::string, std::string> replacements)
	{
		Shader* shader = new Shader();
		ShaderSource source = ReadFileAsString(shaderPath);

		shader->m_ID = CreateProgram(shader, source, replacements);

		return shader;
	}

	Shader* Shader::Create(const char* vertexSrc, const char* fragmentSrc, std::map<std::string, std::string> replacements)
	{
		Shader* shader = new Shader();
		ShaderSource source = { std::string(vertexSrc),std::string(fragmentSrc) };

		shader->m_ID = CreateProgram(shader, source, replacements);

		return shader;
	}

	GLuint Shader::CreateProgram(Shader* shader, ShaderSource& source, std::map<std::string, std::string> replacements)
	{
		PreprocessShader(source.VertexSource, replacements);
		PreprocessShader(source.FragmentSource, replacements);
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

		return program;
	}

	void Shader::PreprocessShader(std::string& source, std::map<std::string, std::string> replacements)
	{
		std::string::size_type search_index = 0;
		size_t dollar_index;
		while ((dollar_index = source.find_first_of('$', search_index)) != std::string::npos)
		{
			if (source[dollar_index + 1] != '{')
				continue;

			size_t close_brace_index = source.find_first_of('}', dollar_index);
			JOLT_ASSERT(close_brace_index != std::string::npos, "No closing brace");
			search_index = close_brace_index + 1;
			std::string token = source.substr(dollar_index + 2, close_brace_index - dollar_index - 2);
			size_t equal_sign_index = token.find_first_of('=');
			bool has_equal_sign = equal_sign_index != std::string::npos;

			std::string key = token.substr(0, equal_sign_index);

			auto it = replacements.find(key);
			if (it == replacements.end()) // use default replacement if provided
			{
				JOLT_ASSERT(has_equal_sign, "Key:", key, "was not provided a replacement and has no default value");
				std::string val = token.substr(equal_sign_index + 1);
				source.replace(dollar_index, close_brace_index - dollar_index + 1, val);
			}
			else
			{
				source.replace(dollar_index, close_brace_index - dollar_index + 1, it->second);
			}
		}
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
		GLint current_program; glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
		if (current_program == m_ID)
		{
			glUseProgram(0);
		}
		glDeleteProgram(m_ID);
	}

	// Uniform Setting
	GLint Shader::GetUniformLocation(const std::string& name) const
	{
#if defined(JOLT_DEBUG) || defined(JOLT_DISTRIBUTION)
		GLint current_shader;
		glGetIntegerv(GL_CURRENT_PROGRAM, &current_shader);
		JOLT_ASSERT(current_shader == m_ID, "Did you forget to bind?");
#endif
		if (m_UniformLocations.find(name) != m_UniformLocations.end())
			return m_UniformLocations[name];

		GLint location = glGetUniformLocation(m_ID, name.c_str());
		JOLT_ASSERT(location != -1, name, "is not a vaild uniform");
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