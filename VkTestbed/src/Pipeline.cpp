#include "Pipeline.h"

#include "config/Assert.h"
#include "config/Types.h"

#include <iostream>
#include <fstream>

Pipeline::Pipeline(const std::string& vertPath, const std::string& fragPath)
{
	CreateGraphicsPipeline(vertPath, fragPath);
}

std::vector<char> Pipeline::ReadFile(const std::string& filepath)
{
	//                           seek to end     read as binary
	std::ifstream file(filepath, std::ios::ate | std::ios::binary);

	VK_ASSERT(file.is_open(), "Failed to open file: /" + filepath);

	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

void Pipeline::CreateGraphicsPipeline(const std::string& vertPath, const std::string& fragPath)
{
	std::vector<char> vertSrc = ReadFile(vertPath);
	std::vector<char> fragSrc = ReadFile(fragPath);

	std::cout << "Vertex shader code size: " << vertSrc.size() << '\n';
	std::cout << "Fragment shader code size: " << fragSrc.size() << '\n';
}
