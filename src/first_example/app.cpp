#include "first_example/app.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "GLFW/glfw3.h"
#include "vulkan/vulkan_core.h"
using namespace FirstExample;

void HelloTriangleApplication::Run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

void HelloTriangleApplication::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Hello Triangle", nullptr,
                            nullptr);
}

void HelloTriangleApplication::initVulkan() { createInstance(); }

void HelloTriangleApplication::createInstance() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char *> requiredExtensions;
  for (uint32_t i = 0; i < glfwExtensionCount; i++) {
    requiredExtensions.emplace_back(glfwExtensions[i]);
  }

  requiredExtensions.emplace_back(
      VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

  createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  createInfo.enabledExtensionCount = requiredExtensions.size();
  createInfo.ppEnabledExtensionNames = requiredExtensions.data();

  // Will look into this later
  createInfo.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to create instance!");
  }
}

void HelloTriangleApplication::checkAvailableExtensions() {
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                         availableExtensions.data());
  std::cout << "Available extension:" << std::endl;
  for (const VkExtensionProperties &extension : availableExtensions) {
    std::cout << '\t' << extension.extensionName << std::endl;
  }
}

void HelloTriangleApplication::mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void HelloTriangleApplication::cleanup() {
  vkDestroyInstance(instance, nullptr);
  glfwDestroyWindow(window);
  glfwTerminate();
}
