#include <atomic>
#include <gtest/gtest.h>
#include <magma/core/thread_pool.h>

TEST(thread_pool, default_constructor_creates_at_least_one_thread) {
  std::atomic<int> counter{0};
  magma::thread_pool pool{[&counter] { ++counter; }};
  EXPECT_GT(pool.nthreads(), 0);
  pool.join();
  EXPECT_GT(counter, 0);
}

TEST(thread_pool, nthreads_constructor_creates_exactly_n_threads) {
  constexpr auto nthreads = 7ul;

  std::atomic<int> counter{0};
  magma::thread_pool pool{nthreads, [&counter] { ++counter; }};
  EXPECT_EQ(pool.nthreads(), nthreads);
  pool.join();
  EXPECT_EQ(counter, nthreads);
}

TEST(thread_pool, constructing_empty_pool_throws_logic_error) {
  auto nthreads = 0;

  EXPECT_THROW(magma::thread_pool(0, [] {}), std::logic_error);
}

