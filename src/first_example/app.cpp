#include "first_example/app.hpp"
#include <cstdint>
#include <cstring>
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

void HelloTriangleApplication::initVulkan() {
  createInstance();
  pickPhysicalDevice();
}

void HelloTriangleApplication::pickPhysicalDevice() {
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw std::runtime_error("no compatible device found");
  }

  std::vector<VkPhysicalDevice> availableDevices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, availableDevices.data());

  for (const VkPhysicalDevice &device : availableDevices) {
    if (isDeviceSuitable(device)) {
      physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("failed to find suitable GPU!");
  }
}

bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device) {
  VkPhysicalDeviceProperties deviceProperties;
  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
         deviceFeatures.geometryShader;
}

void HelloTriangleApplication::createInstance() {
  validationLayers.emplace_back("VK_LAYER_KHRONOS_validation");
  if (enableValidationLayers && !checkValidationLayerSupport()) {
    throw std::runtime_error("validation layers requested but not available");
  }

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

  // This is for validation layers
  createInfo.enabledLayerCount = 0;

  if (enableValidationLayers) {
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
  }

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

bool HelloTriangleApplication::checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char *&layerName : validationLayers) {
    bool found = false;
    for (VkLayerProperties &layer : availableLayers) {
      if (strcmp(layer.layerName, layerName) == 0) {
        found = true;
        break;
      }
    }

    if (!found) {
      return false;
    }
  }
  return true;
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
