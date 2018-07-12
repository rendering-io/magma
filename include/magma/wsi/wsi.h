/**
 * \file
 */
#ifndef MAGMA_WSI_WSI_H
#define MAGMA_WSI_WSI_H

/**
 * Consumers of libMagmaWSIMain can define this function to provide a
 * cross-platform program entry function.
 * \return Returns an implementation-defined integer value.
 */
extern int magma_main();

namespace magma {
namespace wsi {

class window;

/**
 * Initialises the WSI session.
 * \return void
 */
auto init() -> void;

/**
 * Terminates the WSI session and cleans up resources.
 * \return void
 */
auto term() -> void;

/**
 * Polls the WSI message queue, processing any outstanding messages.
 * \return True if the event loop should continue executing, or false if quit
 *         message has been posted.
 */
auto poll() -> bool;

/**
 * Posts a quit status, causing the message polling loop to quit.
 * \param res The status code associated with the quit request, retrieved via
 *            \ref magma::wsi::quit_status().
 * \return void
 */
auto post_quit(int res) -> void;

/**
 * Get the status value posted as the quit message.
 * \return Returns the status code posted via \ref magma::wsi::post_quit().
 */
auto quit_status() -> int;
}
} // namespace magma

#endif // MAGMA_WSI_WSI_H

