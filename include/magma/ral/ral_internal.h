/**
 * \file
 */
#ifndef MAGMA_RAL_RAL_INTERNAL_H
#define MAGMA_RAL_RAL_INTERNAL_H

#include "magma/core/range.h"
#include "ral.h"

namespace magma {
namespace ral {
namespace internal {

class device;

/**
 * Abstract base class for renderer instances.
 */
class instance {
public:
  /**
   * Destructor.
   */
  virtual ~instance();

  /**
   * Gets an iteration range encompassing the set of installed GPus.
   * \return Returns an iteration range encompassing the set of installed GPus.
   */
  virtual auto physical_devices() const -> input_range<physical_device> = 0;

  /**
   * Creates a new logical device corresponding to a particular physical device.
   * \param pdev The physical device to construct a new logical device for.
   * \return Returns a owning pointer to a new logical device.
   */
  virtual auto create_device(const physical_device &pdev)
      -> std::unique_ptr<device> = 0;
};

/**
 * Abstract base class for logical devices.
 */
class device {
public:
  /**
   * Destructor.
   */
  virtual ~device();
};

} // namespace internal
} // namespace ral
} // namespace magma

#endif // MAGMA_RAL_RAL_INTERNAL_H

