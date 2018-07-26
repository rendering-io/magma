#include <gtest/gtest.h>
#include <iostream>
#include <magma/vk/vk.h>

using namespace magma;

TEST(instance, default_construction_does_not_throw) {
  ASSERT_NO_THROW(vk::instance{});
}

TEST(instance, default_construction_creates_non_null_handle) {
  vk::instance instance{};
  ASSERT_NE(instance, VkInstance{VK_NULL_HANDLE});

  VkInstance handle = instance;
  ASSERT_NE(handle, VkInstance{VK_NULL_HANDLE});
}

TEST(instance, physical_devices_returns_non_empty_range) {
  vk::instance instance{};
  auto devices = instance.physical_devices();
  ASSERT_NE(devices.begin(), devices.end());
}

