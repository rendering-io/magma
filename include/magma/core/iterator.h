/**
 * \file
 */
#ifndef MAGMA_CORE_ITERATOR_H
#define MAGMA_CORE_ITERATOR_H

namespace magma {

template <typename T> class input_iterator;

template <typename T>
auto operator==(const input_iterator<T> &a, const input_iterator<T> &b) -> bool;

template <typename T>
auto operator!=(const input_iterator<T> &a, const input_iterator<T> &b) -> bool;

/**
 * A type-erasing input iterator.
 */
template <typename T> class input_iterator {
private:
  class base {
  public:
    virtual auto operator++() -> base & = 0;
    virtual auto operator*() -> T & = 0;
    virtual auto operator-> () -> T * = 0;
    virtual auto operator==(const base &rhs) -> bool = 0;
    virtual auto clone() -> std::unique_ptr<base> = 0;
  };

  template <typename Iter> class wrapper : public base {
  public:
    wrapper(const Iter &i) : _wrapped{i} {}
    auto operator++() -> base & override {
      ++_wrapped;
      return *this;
    }
    auto operator*() -> T & override { return _wrapped.operator*(); }
    auto operator-> () -> T * override { return _wrapped.operator->(); }

    auto operator==(const base &rhs) -> bool override {
      auto &r = reinterpret_cast<const wrapper<Iter> &>(rhs);
      return _wrapped == r._wrapped;
    }
    auto clone() -> std::unique_ptr<base> override {
      return std::unique_ptr<base>(new wrapper<Iter>(_wrapped));
    }

  private:
    Iter _wrapped;
  };

public:
  /**
   * Default constructor.
   */
  input_iterator();

  /**
   * Copy-constructor.
   */
  input_iterator(const input_iterator &);

  // TODO: sfinae based on whether U is an iterator.
  /**
   * Constructor. Constructs a \ref magma::input_iterator from an iterator.
   * \param u The input iterator to construct this object from.
   */
  template <typename U> input_iterator(const U &u);

  /**
   * Copy-assignment operator.
   * \return Returns a reference to this iterator following the assignment.
   */
  auto operator=(const input_iterator &) -> input_iterator &;

  /**
   * Postfix increment operator.
   * \return Returns a copy of this iterator prior to the increment.
   */
  auto operator++(int) -> input_iterator;

  /**
   * Prefix increment operator.
   * \return Returns a reference to this iterator following the increment.
   */
  auto operator++() -> input_iterator &;

  /**
   * Dereference operator.
   * \return Returns a reference to the element pointed to by the iterator.
   */
  auto operator*() -> T &;

  /**
   * Arrow operator.
   * \return Returns a pointer to the element pointed to by the iterator.
   */
  auto operator-> () -> T *;

private:
  std::unique_ptr<base> _iter;

  friend auto operator==
      <>(const input_iterator<T> &a, const input_iterator<T> &b) -> bool;
};

template <typename T> input_iterator<T>::input_iterator() {}

template <typename T>
input_iterator<T>::input_iterator(const input_iterator &i)
    : _iter{i._iter->clone()} {}

template <typename T>
template <typename U>
input_iterator<T>::input_iterator(const U &u) : _iter{new wrapper<U>{u}} {}

template <typename T>
auto input_iterator<T>::operator=(const input_iterator &i) -> input_iterator & {
  _iter = i._iter->clone();
  return *this;
}

template <typename T>
auto input_iterator<T>::operator++(int) -> input_iterator<T> {
  // Copy first, then increment the original.
  auto tmp = *this;
  ++(*_iter);
  return tmp;
}

template <typename T>
auto input_iterator<T>::operator++() -> input_iterator<T> & {
  ++(*_iter);
  return *this;
}

template <typename T> auto input_iterator<T>::operator*() -> T & {
  return _iter->operator*();
}

template <typename T> auto input_iterator<T>::operator-> () -> T * {
  return _iter->operator->();
}

/**
 * Equality comparison operator.
 * \param a The left-hand side of the equality operator.
 * \param b The right-hand side of the equality operator.
 * \return True if a pair of iterators are equal, false otherwise.
 */
template <typename T>
auto operator==(const input_iterator<T> &a, const input_iterator<T> &b)
    -> bool {
  if (a._iter && b._iter)
    return *a._iter == *b._iter;
  else if (!(a._iter || b._iter))
    return true;
  return false;
}

/**
 * Inequality comparison operator.
 * \param a The left-hand side of the inequality operator.
 * \param b The right-hand side of the inequality operator.
 * \return True if a pair of iterators are not equal, false otherwise.
 */
template <typename T>
auto operator!=(const input_iterator<T> &a, const input_iterator<T> &b)
    -> bool {
  return !(a == b);
}

} // namespace magma

#endif // MAGMA_CORE_ITERATOR_H

