#include <iostream>
#include <magma/wsi/window.h>
#include <magma/wsi/wsi.h>
#include <stdexcept>

using namespace magma;

int magma_main() {
  // Holds the return value of magma_main.
  int ret_value = 0;

  try {
    // First we need to initialize the WSI session.
    wsi::init();

    // Create a WSI window.
    wsi::window w;

    // Register a callback to trigger when the window is destroyed. Here we
    // simply post a quit message, causing the event loop to stop polling.
    w.register_callback(wsi::window::event::destroy,
                        [](wsi::window &, void *) { wsi::post_quit(0); });

    // Loop inedfinitely, handling messages and executing the loop body until
    // we receive the quit message.
    while (magma::wsi::poll()) {
    }

    // Set return value to posted quit status.
    ret_value = wsi::quit_status();

  } catch (std::exception &e) {
    // Catch exception and print.
    std::cerr << e.what() << "\n";
    ret_value = -1;
  }

  // Clean up WSI.
  wsi::term();

  return ret_value;
}

