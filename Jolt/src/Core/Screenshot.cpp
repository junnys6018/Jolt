#include "pch.h"
#include "Screenshot.h"
#include <stb_image_write.h>
#include <glad/glad.h>

bool Screenshot::Capture()
{
	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	GLint width = dims[2];
	GLint height = dims[3];

	void* data = new char[width * height * 3];
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_flip_vertically_on_write(1);

	std::time_t time = std::time(0);
	std::tm* date = std::localtime(&time);
	char date_string[50];
	std::sprintf(date_string, "%i-%i-%i_%i-%.2i-%.2i_sceenshot.png", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec);

	bool success = stbi_write_png(date_string, width, height, 3, data, width * 3) == 1;
	if (success)
		LOG_INFO("Took Screenshot");
	else
		LOG_INFO("Failed to take screenshot");
	delete[] data;
	return success;
}
	