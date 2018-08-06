#include <magma/wsi/window.h>
#include <magma/wsi/wsi.h>
#include <tchar.h>
#include <mutex>

using namespace magma::wsi;

namespace {

std::once_flag window_class_registered;
TCHAR magma_window_class[] = _T("magma_window_class");
int quit_return_code = 0;

LRESULT CALLBACK window_proc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam) {
  auto wnd = reinterpret_cast<window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
  switch (msg)
  {
  case WM_DESTROY:
    wnd->handle_event(window::event::destroy);
    return 0;
  default:
    break;
  }
  return DefWindowProc(handle, msg, wparam, lparam);
}

void register_window_class() {
  WNDCLASSEX wcex{};
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = window_proc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = sizeof(window*);
  wcex.hInstance = nullptr;
  wcex.hIcon = nullptr;
  wcex.hCursor = nullptr;
  wcex.hbrBackground = nullptr;
  wcex.lpszMenuName = nullptr;
  wcex.lpszClassName = magma_window_class;
  wcex.hIconSm = nullptr;
  if (!RegisterClassEx(&wcex))
    throw std::runtime_error{ "Failed to register window class." };
}

}

auto magma::wsi::poll() -> bool {
  MSG msg;
  while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
  {
    // Check for a quit message, exiting the loop if we encounter it.
    if (WM_QUIT == msg.message) {
      quit_return_code = msg.wParam;
      return false;
    }

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return true;
}

auto magma::wsi::quit_status() -> int {
  return quit_return_code;
}

auto magma::wsi::post_quit(int i) -> void {
  ::PostQuitMessage(i);
}

auto magma::wsi::init() -> void { }

auto magma::wsi::term() -> void { }

window::window() {
  // Ensure that the window class is registered.
  std::call_once(window_class_registered, register_window_class);

  LPCTSTR window_name = nullptr;
  _window = CreateWindow(magma_window_class, window_name, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    nullptr,
    nullptr,
    nullptr,
    nullptr
  );

  // Store a reference to this window, for retrieval in the window proc.
  SetWindowLongPtr(_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

  ShowWindow(_window, SW_SHOW);
}

auto window::handle_event(window::event e) -> void {
  auto event_callbacks =
    _callbacks.find(std::underlying_type_t<window::event>(e));
  if (end(_callbacks) != event_callbacks) {
    for (auto &c : event_callbacks->second) {
      c._callback(*this, c._user_data);
    }
  }
}

auto window::register_callback(window::event e, window::event_callback c,
  void *u) -> void {
  registered_callback r{ c, u };
  _callbacks[std::underlying_type_t<window::event>(e)].emplace_back(
    std::move(r));
}
