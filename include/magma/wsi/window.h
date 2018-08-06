/**
 * \file
 */
#ifndef MAGMA_WSI_WINDOW_H
#define MAGMA_WSI_WINDOW_H

#include <list>
#include <unordered_map>

#if defined(WIN32)
#include <Windows.h>
#elif defined(__linux__)
#include <xcb/xcb.h>
#endif

namespace magma {
namespace wsi {

/**
 * Encapsulates a native (XCB/Win32) window.
 */
class window {
public:
  /** Callback type for handling window events. */
  using event_callback = void (*)(window &, void *);

  /** Window event enumerated type. */
  enum class event { destroy };

  /** Default constructor. */
  window();

  /** Deleted copy-constructor. */
  window(const window &) = delete;

  /**
   * Registers a callback for a specific window event.
   * \param e The window event type.
   * \param c The callback function to register.
   * \param user Optional user data to be passed to the callback.
   * \return void
   */
  auto register_callback(event e, event_callback c, void *user = nullptr)
      -> void;

  /**
   * Process a window event, by executing any callbacks registered vis \ref
   * register_callback().
   * \param e The window event type.
   * \return void
   */
  auto handle_event(event e) -> void;

private:
  // Event handling callback records.
  struct registered_callback {
    event_callback _callback;
    void *_user_data;
  };
  std::unordered_map<std::underlying_type<event>::type,
                     std::list<registered_callback>>
      _callbacks;

#if defined(WIN32)
  // The native window handle.
  HWND _window;
#elif defined(__linux__)
  // The native window handle.
  xcb_window_t _window;
#endif
};
} // namespace wsi
} // namespace magma

#endif // MAGMA_WSI_WINDOW_H

