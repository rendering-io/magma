/**
 * \file
 */
#ifndef MAGMA_VK_VK_H
#define MAGMA_VK_VK_H

#include <memory>
#include <vulkan/vulkan.h>

namespace magma {
namespace vk {

/**
 * A Vulkan instance, which holds global driver state and isolation.
 */
class instance {
private:
  struct impl;

public:
  /** Default constructor. */
  instance();

  /** Move-constructor. */
  instance(instance &&);

  /** Deleted copy-constructor. */
  instance(const instance &) = delete;

  /** Destructor. */
  ~instance();

  /** Get the underlying VkInstance handle. */
  operator VkInstance();

  /** Get the underlying VkInstance handle. */
  operator const VkInstance() const;

private:
  std::unique_ptr<impl> _impl;
};

class physical_device {};

class device {
private:
  struct impl;
};

} // namespace vk
} // namespace magma

#endif // MAGMA_VK_VK_H

