#include <magma/core/thread_pool.h>

using namespace magma;

namespace {
auto get_default_nthreads() {
  // Defaults to the number of concurrent hardware threads minus 1, minimum 1.
  auto n = std::thread::hardware_concurrency();
  return n <= 1 ? 1 : n - 1;
}
} // namespace

thread_pool::thread_pool(std::function<void()> f)
    : thread_pool{get_default_nthreads(), f} {}

thread_pool::thread_pool(size_t n, std::function<void()> f) {
  if (0 == n)
    throw std::logic_error{"Thread pools must contain at least one thread."};

  threads_.reserve(n);
  for (auto i = 0ul; i < n; ++i)
    threads_.push_back(std::thread{f});
}

thread_pool::~thread_pool() { join(); }

auto thread_pool::nthreads() const -> size_t {
  return threads_.size();
}

auto thread_pool::join() -> void {
  std::lock_guard<std::mutex> lock{mutex_};
  // Join each thread in turn and wait for completion. We need the lock because
  // we otherwise have a potential race condition on the joinable/join pair.
  for (auto &t : threads_) {
    if (t.joinable())
      t.join();
  }
}

