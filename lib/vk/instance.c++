#include "internal.h"
#include <magma/vk/vk.h>
#include <system_error>

using namespace magma::vk;

namespace {

// Queries the set of available extensions.
auto get_available_extensions() -> std::vector<VkExtensionProperties> {
  uint32_t count = 0;
  auto result =
      vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
  if (VK_SUCCESS != result)
    throw std::system_error{result, internal::get_error_category()};

  std::vector<VkExtensionProperties> properties{count};
  result = vkEnumerateInstanceExtensionProperties(nullptr, &count,
                                                  properties.data());
  if (VK_SUCCESS != result)
    throw std::system_error{result, internal::get_error_category()};
  return properties;
}

} // namespace

instance::instance() : _instance{VK_NULL_HANDLE} {
  auto create_info =
      VkInstanceCreateInfo{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                           nullptr,
                           0,
                           nullptr,
                           0,
                           nullptr,
                           0,
                           nullptr};

  auto res = vkCreateInstance(&create_info,
                              internal::get_allocation_callbacks(), &_instance);
  if (VK_SUCCESS != res)
    throw std::system_error{res, internal::get_error_category()};
}

instance::~instance() {
  vkDestroyInstance(_instance, internal::get_allocation_callbacks());
}

instance::operator VkInstance() { return _instance; }

instance::operator const VkInstance() const { return _instance; }

auto instance::physical_devices() const
    -> input_range<magma::ral::physical_device> {
  // Initialize the physical device list.
  std::call_once(_init_physical_devices, [this]() mutable {
    uint32_t ndevices = 0;
    auto result = vkEnumeratePhysicalDevices(_instance, &ndevices, nullptr);
    if (VK_SUCCESS != result)
      throw std::system_error{result, internal::get_error_category()};

    std::vector<VkPhysicalDevice> devices;
    devices.resize(ndevices);
    _physical_devices.reserve(ndevices);
    result = vkEnumeratePhysicalDevices(_instance, &ndevices, devices.data());
    if (VK_SUCCESS != result)
      throw std::system_error{result, internal::get_error_category()};
    for (auto dev : devices)
      _physical_devices.emplace_back(dev);
  });

  return input_range<magma::ral::physical_device>{begin(_physical_devices),
                                                  end(_physical_devices)};
}

auto instance::create_device(const magma::ral::physical_device &pdev)
    -> std::unique_ptr<magma::ral::internal::device> {
  auto vk_dev = reinterpret_cast<const magma::vk::physical_device &>(pdev);

  VkDeviceCreateInfo create_info{};
  VkDevice device = VK_NULL_HANDLE;
  auto result = vkCreateDevice(vk_dev, &create_info,
                               internal::get_allocation_callbacks(), &device);

  return nullptr;
}

