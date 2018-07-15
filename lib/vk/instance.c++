#include "internal.h"
#include <magma/vk/vk.h>
#include <system_error>

using namespace magma::vk;

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

