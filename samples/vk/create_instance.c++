#include <iostream>
#include <magma/vk/vk.h>
#include <stdexcept>

using namespace magma;

int magma_main() {
  try {
    // Create a new instance.
    vk::instance instance;
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
  }
}

