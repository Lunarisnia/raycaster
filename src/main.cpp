#include <cstdlib>
#include <exception>
#include <iostream>
#include "first_example/app.hpp"

int main() {
  FirstExample::HelloTriangleApplication app;
  try {
    app.Run();
  } catch (std::exception& err) {
    std::cout << err.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
