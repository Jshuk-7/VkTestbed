#include "Window.h"
#include "config/Assert.h"

Window::Window(const std::string& title, u32 width, u32 height)
	: m_Title(title), m_Width(width), m_Height(height)
{
	Init();
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::Closed() const
{
	return glfwWindowShouldClose(m_Window);
}

void Window::PollInput() const
{
	glfwPollEvents();
}

void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
	VK_CHECK(glfwCreateWindowSurface(instance, m_Window, nullptr, surface), "Failed to create window surface!");
}

void Window::Init()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, FramebufferResizedCallback);
}

void Window::FramebufferResizedCallback(GLFWwindow* window, int fbWidth, int fbHeight)
{
	Window* wnd = reinterpret_cast<Window*>(window);

	wnd->m_Width = fbWidth;
	wnd->m_Height = fbHeight;
	wnd->m_FramebufferResized = true;
}