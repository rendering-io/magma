#include "internal.h"
#include <magma/vk/vk.h>
#include <system_error>

using namespace magma::vk;

struct instance::impl {
  impl() = default;
  ~impl();

  VkInstance handle;

  internal::global_fn_table global_fn;
  internal::instance_fn_table instance_fn;
};

instance::impl::~impl() {
  instance_fn.destroy_instance(handle, internal::get_allocation_callbacks());
}

instance::instance() : _impl{std::make_unique<impl>()} {
  // Load the dispatch table for global (non-instance) functions.
  internal::get_global_fn(_impl->global_fn);
  auto create_info =
      VkInstanceCreateInfo{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                           nullptr,
                           0,
                           nullptr,
                           0,
                           nullptr,
                           0,
                           nullptr};

  auto res = _impl->global_fn.create_instance(
      &create_info, internal::get_allocation_callbacks(), &_impl->handle);
  if (VK_SUCCESS != res)
    throw std::system_error{res, internal::get_error_category()};

  // Load the per-instance dispatch table.
  internal::get_instance_fn(_impl->handle, _impl->instance_fn);
}

instance::~instance() {}

instance::operator VkInstance() { return _impl->handle; }

instance::operator const VkInstance() const { return _impl->handle; }

