#include <gtest/gtest.h>
#include <magma/core/iterator.h>
#include <vector>

using namespace magma;

TEST(input_iterator, copy_constructible) {
  std::vector<int> v;
  v.push_back(1);

  auto a = input_iterator<int>{begin(v)};
  input_iterator<int> b{a};

  ASSERT_EQ(b, a);
}

TEST(input_iterator, copy_assignable) {
  std::vector<int> v;
  v.push_back(1);

  auto a = input_iterator<int>{begin(v)};
  auto b = input_iterator<int>{};
  b = a;

  ASSERT_EQ(b, a);
}

TEST(input_iterator, equality) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);

  auto a = input_iterator<int>{begin(v)};
  auto b = input_iterator<int>{begin(v)};
  ASSERT_TRUE(b == a);

  b++;
  ASSERT_FALSE(b == a);
}

TEST(input_iterator, inequality) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);

  auto a = input_iterator<int>{begin(v)};
  auto b = input_iterator<int>{begin(v)};
  ASSERT_FALSE(b != a);

  b++;
  ASSERT_TRUE(b != a);
}

TEST(input_iterator, prefix_increment) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);

  auto i = begin(v);
  auto a = input_iterator<int>{i};
  auto b = ++a;

  i++;
  auto c = input_iterator<int>{i};
  ASSERT_TRUE(b == a);
  ASSERT_TRUE(b == c);
}

TEST(input_iterator, postfix_increment) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);

  auto i = begin(v);
  auto a = input_iterator<int>{i};
  auto b = a;
  auto c = a++;

  i++;
  auto d = input_iterator<int>{i};
  ASSERT_TRUE(b != a);
  ASSERT_TRUE(b == c);
  ASSERT_TRUE(a == d);
}

TEST(input_iterator, dereference) {
  std::vector<int> v;
  v.push_back(1);

  auto a = input_iterator<int>{begin(v)};
  ASSERT_EQ(*a, *begin(v));
}

TEST(input_iterator, arrow) {
  struct s {
    int i;
  };
  std::vector<s> v;
  v.push_back({1});

  auto a = input_iterator<s>{begin(v)};
  ASSERT_EQ(&a->i, &v[0].i);
}

