#include <gtest/gtest.h>
#include <magma/vk/vk.h>

using namespace magma;

TEST(instance, default_construction_does_not_throw) {
  ASSERT_NO_THROW(auto i = vk::instance{});
}

TEST(instance, default_construction_creates_non_null_handle) {
  auto i = vk::instance{};
  ASSERT_NE(i, VkInstance{VK_NULL_HANDLE});

  VkInstance handle = i;
  ASSERT_NE(handle, VkInstance{VK_NULL_HANDLE});
}

