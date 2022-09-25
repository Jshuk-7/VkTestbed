#pragma once

#include <iostream>

#define VK_ASSERT(x, message) { if (!(x)) { std::cout << message << '\n'; __debugbreak(); } }