#include <gtest/gtest.h>
#include <iostream>
#include <magma/ral/ral.h>

using namespace magma;

TEST(instance, default_construction_does_not_throw) {
  ASSERT_NO_THROW(ral::instance{});
}

TEST(instance, physical_devices_returns_non_empty_range) {
  ral::instance instance{};
  auto devices = instance.physical_devices();
  ASSERT_NE(devices.begin(), devices.end());
}

