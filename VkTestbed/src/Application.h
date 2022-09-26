#pragma once

#include "config/Types.h"
#include "SwapChain.h"
#include "Pipeline.h"
#include "Device.h"
#include "Window.h"
#include "Model.h"

#include <memory>
#include <vector>

class Application
{
public:
	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	~Application();

	static constexpr u32 WIDTH = 800;
	static constexpr u32 HEIGHT = 600;

	void Run();

private:
	void LoadModels();
	void CreatePipelineLayout();
	void CreatePipeline();
	void CreateCommandBuffers();
	void DrawFrame();

	void ReCreateSwapChain();
	void RecordCommandBuffer(int imageIndex);

private:
	Window m_Window{ "Vk Testbed", WIDTH, HEIGHT };
	Device m_Device{ m_Window };
	std::unique_ptr<SwapChain> m_SwapChain;
	std::unique_ptr<Pipeline> m_Pipeline;
	VkPipelineLayout m_PipelineLayout;
	std::vector<VkCommandBuffer> m_CommandBuffers;

	std::unique_ptr<Model> m_Model;
};

