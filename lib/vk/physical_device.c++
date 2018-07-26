#include "magma/vk/vk.h"

using namespace magma::vk;

physical_device::physical_device(VkPhysicalDevice device) : _device{device} {
  vkGetPhysicalDeviceProperties(_device, &_properties);
  vkGetPhysicalDeviceMemoryProperties(_device, &_memory_properties);
}

auto physical_device::name() const -> const char * {
  return _properties.deviceName;
}

