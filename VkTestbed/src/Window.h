#pragma once

#include "config/Types.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

class Window
{
public:
	Window(const std::string& title, u32 width, u32 height);
	~Window();
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;

	bool Closed() const;
	void PollInput() const;

private:
	void Init();

private:
	std::string m_Title;
	u32 m_Width, m_Height;
	GLFWwindow* m_Window;
};
