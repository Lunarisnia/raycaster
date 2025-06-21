#include "first_example/app.hpp"
using namespace FirstExample;

void HelloTriangleApplication::Run() {
  initVulkan();
  mainLoop();
  cleanup();
}

void HelloTriangleApplication::initVulkan() {}

void HelloTriangleApplication::mainLoop() {}

void HelloTriangleApplication::cleanup() {}
