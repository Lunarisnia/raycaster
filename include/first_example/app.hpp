#pragma once
#include <optional>
#include <vector>
#include "vulkan/vulkan_core.h"
#define GLFW_INCLUDE_VULKAN
#include <cstdint>
#include "GLFW/glfw3.h"
namespace FirstExample {
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
};

class HelloTriangleApplication {
 private:
  GLFWwindow* window;
  VkInstance instance;
  VkDevice device;
  VkPhysicalDevice physicalDevice;
  VkPhysicalDeviceFeatures deviceFeatures;
  VkQueue graphicsQueue;
  VkSurfaceKHR surface;

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  std::vector<const char*> validationLayers;
  const bool enableValidationLayers = true;

 private:
  void initWindow();
  void initVulkan();
  void createInstance();
  void mainLoop();
  void cleanup();

  void pickPhysicalDevice();
  bool isDeviceSuitable(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  void createLogicalDevice();
  void checkAvailableExtensions();
  bool checkValidationLayerSupport();
  void createSurface();

 public:
  void Run();
};
}  // namespace FirstExample
