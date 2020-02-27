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

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// TODO LOG infolog
			std::cout << infoLog.data() << std::endl;
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

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			// TODO LOG infolog
			std::cout << infoLog.data() << std::endl;
		}

		return shader;
	}
}