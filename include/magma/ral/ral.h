/**
 * \file
 */
#ifndef MAGMA_RAL_RAL_H
#define MAGMA_RAL_RAL_H

#include <memory>

namespace magma {
namespace ral {

namespace internal {
class instance;
}

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

private:
  std::unique_ptr<internal::instance> _impl;
};

} // namespace ral
} // namespace magma

#endif // MAGMA_RAL_RAL_H

