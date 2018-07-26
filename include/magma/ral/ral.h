/**
 * \file
 */
#ifndef MAGMA_RAL_RAL_H
#define MAGMA_RAL_RAL_H

#include "magma/core/range.h"
#include <memory>

namespace magma {
namespace ral {

namespace internal {
class instance;
class device;
}

class device;
class physical_device;

/**
 * A RAL instance, which holds global driver state.
 */
class instance {
public:
  /** Default constructor. */
  instance();

  /** Move-constructor. */
  instance(instance &&) = default;

  /** Deleted copy-constructor. */
  instance(const instance &) = delete;

  /** Destructor. */
  ~instance();

  /**
   * Gets an iteration range containing the installed physical devices.
   * \return Returns an iteration range covering the set of installed physical
   *         devices.
   */
  auto physical_devices() const -> input_range<physical_device>;

  /**
   * Creates a logical device corresponding to a particular physical device.
   * \param pdev The physical device to construct a logical device for.
   * \return Returns a new logical device.
   */
  auto create_device(const physical_device &pdev) -> device;

private:
  std::unique_ptr<internal::instance> _impl;
};

/**
 * A RAL descriptor for a physical device such as a GPU.
 */
class physical_device {
public:
  /**
   * Destructor.
   */
  virtual ~physical_device();

  /**
   * Get the device name.
   * \return Returns the name of the physical device.
   */
  virtual auto name() const -> const char * = 0;
};

/**
 * A RAL logical device.
 */
class device {
private:
  device(std::unique_ptr<internal::device> impl);

public:
private:
  std::unique_ptr<internal::device> _impl;

  friend class instance;
};
} // namespace ral
} // namespace magma

#endif // MAGMA_RAL_RAL_H

