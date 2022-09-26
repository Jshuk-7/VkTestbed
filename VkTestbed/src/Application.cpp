#include "Application.h"

#include "config/Assert.h"

#include <array>

Application::Application()
{
	LoadModels();
	CreatePipelineLayout();
	ReCreateSwapChain();
	CreateCommandBuffers();
}

Application::~Application()
{
	vkDestroyPipelineLayout(m_Device.device(), m_PipelineLayout, nullptr);
}

void Application::Run()
{
	while (!m_Window.Closed())
	{
		m_Window.PollInput();
		DrawFrame();
	}

	vkDeviceWaitIdle(m_Device.device());
}

void Application::LoadModels()
{
	std::vector<Model::Vertex> vertices{
		{ {  0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
		{ {  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
		{ { -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f } }
	};

	m_Model = std::make_unique<Model>(m_Device, vertices);
}

void Application::CreatePipelineLayout()
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pSetLayouts = nullptr;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;

	VK_CHECK(vkCreatePipelineLayout(m_Device.device(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout), "Failed to create pipeline layout!");
}

void Application::CreatePipeline()
{
	PipelineConfigInfo pipelineConfig{};
	Pipeline::DefaultPipelineConfigInfo(pipelineConfig, m_SwapChain->width(), m_SwapChain->height());

	pipelineConfig.renderPass = m_SwapChain->getRenderPass();
	pipelineConfig.pipelineLayout = m_PipelineLayout;
	m_Pipeline = std::make_unique<Pipeline>("shaders/basic.vert.spv", "shaders/basic.frag.spv", m_Device, pipelineConfig);
}

void Application::ReCreateSwapChain()
{
	auto extent = m_Window.GetExtent();
	
	while (extent.width == 0 || extent.height == 0)
	{
		extent = m_Window.GetExtent();
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(m_Device.device());

	m_SwapChain.reset(); // TODO SHOULD BE REMOVED WHEN SUPPLYING NEW SWAPCHAIN WITH OLD!

	m_SwapChain = std::make_unique<SwapChain>(m_Device, extent);
	CreatePipeline();
}

void Application::CreateCommandBuffers()
{
	m_CommandBuffers.resize(m_SwapChain->imageCount());

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = m_Device.getCommandPool();
	allocInfo.commandBufferCount = static_cast<u32>(m_CommandBuffers.size());

	VK_CHECK(vkAllocateCommandBuffers(m_Device.device(), &allocInfo, m_CommandBuffers.data()), "Failed to allocate command buffers!");
}

void Application::RecordCommandBuffer(int imageIndex)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	VK_CHECK(vkBeginCommandBuffer(m_CommandBuffers[imageIndex], &beginInfo), "Failed to begin recording command buffer!");

	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = { 0.2f, 0.2f, 0.2f, 1.0f };
	clearValues[1].depthStencil = { 1.0f, 0 };

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = m_SwapChain->getRenderPass();
	renderPassInfo.framebuffer = m_SwapChain->getFrameBuffer(imageIndex);
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = m_SwapChain->getSwapChainExtent();
	renderPassInfo.clearValueCount = static_cast<u32>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(m_CommandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	m_Pipeline->Bind(m_CommandBuffers[imageIndex]);
	m_Model->Bind(m_CommandBuffers[imageIndex]);
	m_Model->Draw(m_CommandBuffers[imageIndex]);

	vkCmdEndRenderPass(m_CommandBuffers[imageIndex]);

	VK_CHECK(vkEndCommandBuffer(m_CommandBuffers[imageIndex]), "Failed to finish recording command buffer!");
}

void Application::DrawFrame()
{
	u32 imageIndex;
	auto result = m_SwapChain->acquireNextImage(&imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		ReCreateSwapChain();
		return;
	}

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		VK_ASSERT(false, "Failed to acuire next image from swap chain!");

	RecordCommandBuffer(imageIndex);
	result = m_SwapChain->submitCommandBuffers(&m_CommandBuffers[imageIndex], &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_Window.IsResized())
	{
		m_Window.ResetWindowResized();
		ReCreateSwapChain();
		return;
	}

	VK_CHECK(result, "Failed to present image from swap chain!");
}
