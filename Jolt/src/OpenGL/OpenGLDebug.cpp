#include "pch.h"
#include "OpenGLDebug.h"

namespace Jolt {

	static DebugLogLevel s_DebugLogLevel = DebugLogLevel::HighAssert;

	void SetGLDebugLogLevel(DebugLogLevel level)
	{
		s_DebugLogLevel = level;
	}

	void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			if ((int)s_DebugLogLevel > 0)
			{
				std::cout << "[OpenGL Debug HIGH] " << message << std::endl;
			}
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			if ((int)s_DebugLogLevel > 2)
				std::cout << "[OpenGL Debug MEDIUM] " << message << std::endl;
			break;
		case GL_DEBUG_SEVERITY_LOW:
			if ((int)s_DebugLogLevel > 3)
				std::cout << "[OpenGL Debug LOW] " << message << std::endl;
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			if ((int)s_DebugLogLevel > 4)
				std::cout << "[OpenGL Debug NOTIFICATION] " << message << std::endl;
			break;
		}
	}

	void EnableGLDebugging()
	{
		glDebugMessageCallback(OpenGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

}