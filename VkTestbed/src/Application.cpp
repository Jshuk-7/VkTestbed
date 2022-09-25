#include "Application.h"

Application::Application(const std::string& title, u32 width, u32 height)
	: m_Window(title, width, height), m_Pipeline("shaders/basic.vert.spv", "shaders/basic.frag.spv")
{
	
}

void Application::Run()
{
	while (!m_Window.Closed())
	{
		m_Window.PollInput();
	}
}
