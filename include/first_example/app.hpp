#pragma once
#include <cstdint>
#include "GLFW/glfw3.h"
namespace FirstExample {
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
 private:
  GLFWwindow *window;

 private:
  void initWindow();
  void initVulkan();
  void mainLoop();
  void cleanup();

 public:
  void Run();
};
}  // namespace FirstExample
