#pragma once

#include "config/Types.h"
#include "Device.h"

#include <string>
#include <vector>

struct PipelineConfigInfo {
	PipelineConfigInfo() = default;
	PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

	VkViewport viewport{};
	VkRect2D scissor{};
	VkPipelineViewportStateCreateInfo viewportInfo;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
	VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
	VkPipelineMultisampleStateCreateInfo multisampleInfo{};
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
	VkPipelineLayout pipelineLayout = nullptr;
	VkRenderPass renderPass = nullptr;
	uint32_t subpass = 0;
};

class Pipeline
{
public:
	Pipeline() = default;
	Pipeline(const std::string& vertPath, const std::string& fragPath, Device& device, const PipelineConfigInfo& configInfo);
	Pipeline(const Pipeline&) = delete;
	Pipeline& operator=(const Pipeline&) = delete;
	~Pipeline();

	void Bind(VkCommandBuffer commandBuffer);

	static void DefaultPipelineConfigInfo(PipelineConfigInfo& configInfo, uint32_t width, uint32_t height);

private:
	static std::vector<char> ReadFile(const std::string& filepath);

	void CreateGraphicsPipeline(const std::string& vertPath, const std::string& fragPath, const PipelineConfigInfo& configInfo);

	void CreateShaderModule(const std::vector<char> src, VkShaderModule* shaderModule);

private:
	Device& m_Device;
	VkPipeline m_GraphicsPipeline;
	VkShaderModule m_VertexShaderModule;
	VkShaderModule m_FragmentShaderModule;
};

