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
	Window& operator=(const Window&) = delete;

	bool Closed() const;
	void PollInput() const;

	VkExtent2D GetExtent() const { return { m_Width, m_Height }; }

	void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	bool IsResized() const { return m_FramebufferResized; }
	void ResetWindowResized() { m_FramebufferResized = false; }

private:
	static void FramebufferResizedCallback(GLFWwindow* window, int fbWidth, int fbHeight);

	void Init();

private:
	std::string m_Title;
	u32 m_Width, m_Height;
	bool m_FramebufferResized = false;
	GLFWwindow* m_Window;
};
