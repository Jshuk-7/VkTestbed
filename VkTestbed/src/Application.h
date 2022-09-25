#pragma once

#include "config/Types.h"
#include "Pipeline.h"
#include "Window.h"

class Application
{
public:
	Application(const std::string& title = std::string("Vk Testbed"), u32 width = 800, u32 height = 600);
	Application(const Application&) = delete;
	Application operator=(const Application&) = delete;

	void Run();

private:
	Pipeline m_Pipeline;
	Window m_Window;
};

