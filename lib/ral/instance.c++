#include "magma/ral/ral.h"
#include "magma/ral/ral_internal.h"
#include "magma/vk/vk.h"

using namespace magma::ral;

internal::instance::~instance() {}

instance::instance() : _impl{new vk::instance{}} {}

instance::~instance() {}

auto instance::physical_devices() const -> input_range<physical_device> {
  return _impl->physical_devices();
}

auto instance::create_device(const physical_device &pdev) -> device {
  auto ptr = _impl->create_device(pdev);
  return device{std::move(ptr)};
}

