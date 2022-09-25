#include "Window.h"

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

void Window::Init()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
}
