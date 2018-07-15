/**
 * \file
 */
#ifndef MAGMA_VK_VK_H
#define MAGMA_VK_VK_H

#include "magma/ral/ral_internal.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace magma {
namespace vk {

/**
 * A Vulkan instance, which holds global driver state and isolation.
 */
class instance : public magma::ral::internal::instance {
public:
  /** Constructor. */
  instance();

  /** Deleted move-constructor. */
  instance(instance &&) = delete;

  /** Deleted copy-constructor. */
  instance(const instance &) = delete;

  /** Destructor. */
  ~instance();

  /** Get the underlying VkInstance handle. */
  operator VkInstance();

  /** Get the underlying VkInstance handle. */
  operator const VkInstance() const;

private:
  // The Vulkan instance.
  VkInstance _instance;
};

class physical_device {};

class device {
private:
  struct impl;
};

} // namespace vk
} // namespace magma

#endif // MAGMA_VK_VK_H

