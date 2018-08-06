#include "magma/wsi/wsi.h"
#include <Windows.h>

// Program-entry function.
int CALLBACK WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmd_line, int cmd_show) {
  return magma_main();
}