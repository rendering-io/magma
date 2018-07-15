/**
 * \file
 */
#ifndef MAGMA_RAL_RAL_INTERNAL_H
#define MAGMA_RAL_RAL_INTERNAL_H

namespace magma {
namespace ral {
namespace internal {

/**
 * Abstract base class for renderer instances.
 */
class instance {
public:
  /**
   * Destructor.
   */
  virtual ~instance();
};

/**
 * Abstract base class for logical devices.
 */
class device {
  /**
   * Destructor.
   */
  virtual ~device();
};

} // namespace internal
} // namespace ral
} // namespace magma

#endif // MAGMA_RAL_RAL_INTERNAL_H

