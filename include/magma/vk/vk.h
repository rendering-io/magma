/**
 * \file
 */
#ifndef MAGMA_VK_VK_H
#define MAGMA_VK_VK_H

#include "magma/ral/ral_internal.h"
#include <memory>
#include <mutex>
#include <vector>
#include <vulkan/vulkan.h>

namespace magma {
namespace vk {

class physical_device;

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

  /**
   * Gets an iteration range encompassing the set of installed GPus.
   * \return Returns an iteration range encompassing the set of installed GPus.
   */
  auto physical_devices() const
      -> input_range<magma::ral::physical_device> override;

  auto create_device(const magma::ral::physical_device &pdev)
      -> std::unique_ptr<magma::ral::internal::device> override;

private:
  // The Vulkan instance.
  VkInstance _instance;

  // Flag guarding the initialization of the physical devices vector.
  mutable std::once_flag _init_physical_devices;

  // The set of installed physical devices.
  mutable std::vector<physical_device> _physical_devices;
};

/**
 * A descriptor for a Vulkan compatible physical device.
 */
class physical_device : public ral::physical_device {
public:
  /**
   * Constructor.
   * \param device A Vulkan physical device handle.
   */
  physical_device(VkPhysicalDevice device);

  /**
   * Get the device name.
   * \return Returns the name of the physical device.
   */
  auto name() const -> const char * override;

  /**
   * Conversion operator to allow easy conversion to a VkPhysicalDevice handle.
   * \return Returns a VkPhysicalDevice handle.
   */
  operator VkPhysicalDevice() { return _device; }

private:
  // The device handle.
  VkPhysicalDevice _device;

  // Properties for the device itself.
  VkPhysicalDeviceProperties _properties;

  // Memory properties for the device.
  VkPhysicalDeviceMemoryProperties _memory_properties;

  // Properties for the queues families provided by this device.
  std::vector<VkQueueFamilyProperties> _queue_family_properties;
};

class device {
private:
  struct impl;
};

} // namespace vk
} // namespace magma

#endif // MAGMA_VK_VK_H

