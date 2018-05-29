#ifndef MAGMA_CORE_THREAD_POOL_H
#define MAGMA_CORE_THREAD_POOL_H

#include <mutex>
#include <thread>
#include <vector>

namespace magma {

/**
 * A pool of worker threads. The thread pool spawns one or more threads. The
 * thread pool destructor blocks until all threads in the pool have completed
 * execution.
 */
class thread_pool {
public:
  /**
   * Constructs a thread pool with a default number of worker threads (minimum
   * 1).
   * \param f A function object to be executed by all worker threads in the
   * thread pool.
   */
  thread_pool(std::function<void()> f);

  /**
   * Constructs a thread pool with an explicitly specified number of worker
   * threads.
   * \param nthreads The number of worker threads to create (minimum 1).
   * \param f A function object to be executed by all worker threads in the
   * thread pool.
   */
  thread_pool(size_t nthreads, std::function<void()> f);

  /**
   * Deleted copy-constructor.
   */
  thread_pool(const thread_pool &) = delete;

  /**
   * Destructor.
   */
  ~thread_pool();

  /**
   * Gets the number of worker threads in the pool.
   * \return Returns the number of worker threads in the pool.
   */
  auto nthreads() const -> size_t;

  /**
   * Joins the currently executing thread to all worker threads, blocking the
   * current thread of execution until all worker threads have completed.
   * \return void
   */
  auto join() -> void;

private:
  std::mutex mutex_;
  std::vector<std::thread> threads_;
};

} // namespace magma

#endif // MAGMA_CORE_THREAD_POOL_H

