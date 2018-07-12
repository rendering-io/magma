#include <magma/wsi/window.h>
#include <magma/wsi/wsi.h>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <system_error>
#include <unordered_map>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
using namespace magma::wsi;

namespace {

// Unique pointer to provide RAII for XCB events.
using xcb_event_ptr = std::unique_ptr<xcb_generic_event_t, decltype(&free)>;

// Holds the state for an XCB session.
class xcb_session {
public:
  xcb_session();
  xcb_session(const xcb_session &) = delete;

  auto verify_connection() -> void;
  auto poll() -> xcb_event_ptr;

private:
  auto get_intern_atom(const std::string &name, bool only_if_exists)
      -> xcb_atom_t;

  using connection_ptr =
      std::unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)>;

  // The XCB connection to the X11 server.
  connection_ptr _connection;

  xcb_atom_t _wm_protocol_atom;

  xcb_atom_t _wm_delete_window_atom;

  // Provides a mapping from XCB window handles to magma::wsi::window instances.
  std::unordered_map<xcb_window_t, window *> _window_ids;

  friend class magma::wsi::window;
  friend auto magma::wsi::poll() -> bool;
};

struct xcb_error_category : std::error_category {
public:
  auto name() const noexcept -> const char * override;
  auto message(int ev) const -> std::string override;
};

std::unique_ptr<xcb_session> session;
const xcb_error_category xcb_err_category{};

std::mutex xcb_mutex;
auto quit_code = 0;
auto quit = false;

xcb_session::xcb_session()
    : _connection{xcb_connect(nullptr, nullptr), xcb_disconnect} {
  verify_connection();

  _wm_protocol_atom = get_intern_atom("WM_PROTOCOLS", true);
  _wm_delete_window_atom = get_intern_atom("WM_DELETE_WINDOW", false);
}

auto xcb_session::get_intern_atom(const std::string &name, bool only_if_exists)
    -> xcb_atom_t {
  auto cookie = xcb_intern_atom(_connection.get(), only_if_exists, name.size(),
                                name.c_str());
  auto reply = std::unique_ptr<xcb_intern_atom_reply_t, decltype(&free)>{
      xcb_intern_atom_reply(_connection.get(), cookie, 0), free};
  auto atom = reply->atom;
  return atom;
}

auto xcb_session::poll() -> xcb_event_ptr {
  return xcb_event_ptr{xcb_poll_for_event(_connection.get()), free};
}

auto xcb_session::verify_connection() -> void {
  auto err = xcb_connection_has_error(_connection.get());
  if (err)
    throw std::system_error{err, xcb_err_category};
}

auto xcb_error_category::name() const noexcept -> const char * { return "XCB"; }

auto xcb_error_category::message(int e) const -> std::string {
  switch (e) {
  case XCB_CONN_ERROR:
    return "XCB connection error. Typically caused by socket, pipe errors "
           "or other stream errors.";
  case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
    return "XCB extension not supported.";
  case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
    return "Insufficient available memory.";
  case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
    return "Request length exceeds maximum supported the X server.";
  case XCB_CONN_CLOSED_PARSE_ERR:
    return "Error parsing display string.";
  case XCB_CONN_CLOSED_INVALID_SCREEN:
    return "X server does not have a screen matching the requested display.";
  default:
    return "Unrecognized error.";
  }
}

}

auto magma::wsi::poll() -> bool {
  auto e = xcb_event_ptr{nullptr, free};
  while (e = session->poll()) {
    switch (e->response_type & ~0x80) {
    case XCB_CLIENT_MESSAGE: {
      // Cast to a client message.
      auto cli = reinterpret_cast<xcb_client_message_event_t *>(e.get());

      // Get the wsi::window corresponding to this message.
      auto w = session->_window_ids[cli->window];

      // If the client event was a delete message, then call the window event
      // handler.
      if (cli->data.data32[0] == session->_wm_delete_window_atom) {
        w->handle_event(window::event::destroy);
      }
      break;
    }
    }
  }

  return !quit;
}

auto magma::wsi::quit_status() -> int {
  std::lock_guard<std::mutex> lock{xcb_mutex};
  return quit_code;
}

auto magma::wsi::post_quit(int i) -> void {
  std::lock_guard<std::mutex> lock{xcb_mutex};
  quit_code = i;
  quit = true;
}

auto magma::wsi::init() -> void {
  if (session)
    throw std::logic_error{"WSI already initialized."};

  session = std::make_unique<xcb_session>();
}

auto magma::wsi::term() -> void {
  if (!session)
    throw std::logic_error{"WSI not initialized."};

  session.reset();
}

window::window() {
  // Get the X11 connection and screen.
  auto connection = session->_connection.get();
  auto screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

  // Create the underlying window.
  uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  uint32_t values[2] = {screen->white_pixel,
                        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS |
                            XCB_EVENT_MASK_STRUCTURE_NOTIFY};
  _window = xcb_generate_id(connection);
  auto cookie = xcb_create_window(
      connection, XCB_COPY_FROM_PARENT, _window, screen->root, 0, 0, 640, 480,
      0, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, values);

  // Make sure we get client message event for window destroy.
  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, _window,
                      session->_wm_protocol_atom, 4, 32, 1,
                      &session->_wm_delete_window_atom);

  // Register the window.
  session->_window_ids[_window] = this;

  // Make the window visible.
  xcb_map_window(connection, _window);
  xcb_flush(connection);
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
  registered_callback r{c, u};
  _callbacks[std::underlying_type_t<window::event>(e)].emplace_back(
      std::move(r));
}

