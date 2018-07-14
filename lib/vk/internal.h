#ifndef MAGMA_VK_INTERNAL_H
#define MAGMA_VK_INTERNAL_H

#include <system_error>
#include <vulkan/vulkan.h>

namespace magma {
namespace vk {
namespace internal {

using void_fn = void (*)();

auto get_error_category() -> const std::error_category &;
inline auto get_allocation_callbacks() -> VkAllocationCallbacks * {
  return nullptr;
}

struct global_fn_table {
  PFN_vkCreateInstance create_instance;
};

struct instance_fn_table {
  PFN_vkDestroyInstance destroy_instance;
  PFN_vkEnumeratePhysicalDevices enumerate_physical_devices;
};

struct device_fn_table {};

auto get_global_fn(global_fn_table &t) -> void;
auto get_instance_fn(VkInstance instance, instance_fn_table &t) -> void;
auto get_device_fn(device_fn_table &t) -> void;

} // namespace internal
} // namespace vk
} // namespace magma

#endif // MAGMA_VK_INTERNAL_H

