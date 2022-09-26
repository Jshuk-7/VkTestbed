#pragma once

#include "config/Types.h"
#include "Device.h"

#include <vector>

class Model
{
public:
	struct Vertex
	{
		Vec2 Position;
		Vec3 Color;

		static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
		static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
	};

public:
	Model() = default;
	Model(Device& device, const std::vector<Vertex>& vertices);
	~Model();

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void Bind(VkCommandBuffer commandBuffer);
	void Draw(VkCommandBuffer commandBuffer);

private:
	void CreateVertexBuffer(const std::vector<Vertex>& vertices);

private:
	Device& m_Device;
	VkBuffer m_VertexBuffer;
	VkDeviceMemory m_VertexBufferMemory;
	u32 m_VertexCount;
};
