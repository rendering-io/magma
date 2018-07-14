#include <gtest/gtest.h>
#include <magma/core/range.h>
#include <vector>

using namespace magma;

TEST(input_range, range_based_for_equals_source_data) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  auto range = input_range<int>{begin(v), end(v)};

  std::vector<int> out;
  for (auto i : range) {
    out.push_back(i);
  }

  for (auto i = 0; i < v.size(); ++i) {
    ASSERT_EQ(out[i], v[i]);
  }
}

