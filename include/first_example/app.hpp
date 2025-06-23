#pragma once
#define GLFW_INCLUDE_VULKAN
#include <cstdint>
#include "GLFW/glfw3.h"
namespace FirstExample {
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
 private:
  GLFWwindow* window;
  VkInstance instance;

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;

 private:
  void initWindow();
  void initVulkan();
  void createInstance();
  void mainLoop();
  void cleanup();

 public:
  void Run();
};
}  // namespace FirstExample
