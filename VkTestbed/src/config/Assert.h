#pragma once

#include <iostream>

#define VK_ASSERT(x, message) { if (!(x)) { std::cout << message << '\n'; __debugbreak(); } }
#define VK_CHECK(x, message) { if ((x) != VK_SUCCESS) { VK_ASSERT(false, message); } }