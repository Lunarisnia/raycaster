#pragma once
namespace FirstExample {
class HelloTriangleApplication {
 private:
  void initVulkan();
  void mainLoop();
  void cleanup();

 public:
  void Run();
};
}  // namespace FirstExample
