/**
 * \file
 */
#ifndef MAGMA_CORE_RANGE_H
#define MAGMA_CORE_RANGE_H

#include "iterator.h"

namespace magma {

/**
 * A range bounded by a pair of type-erasing input iterators.
 */
template <typename T> class input_range {
public:
  /**
   * Constructor.
   * \param begin An iterator pointing to the first element of the range.
   * \param end An iterator pointing to the first element beyond the end of the
   *            range.
   */
  input_range(const input_iterator<T> &begin, const input_iterator<T> &end);

  /**
   * Get an iterator referencing the start of the range.
   * \return Returns an iterator pointing to the start of the range.
   */
  auto begin() -> input_iterator<T>;

  /**
   * Get an iterator referencing the end of the range.
   * \return Returns an iterator pointing to the end of the range.
   */
  auto end() -> input_iterator<T>;

private:
  input_iterator<T> _begin;
  input_iterator<T> _end;
};

template <typename T>
input_range<T>::input_range(const input_iterator<T> &begin,
                            const input_iterator<T> &end)
    : _begin{begin}, _end{end} {}

template <typename T> auto input_range<T>::begin() -> input_iterator<T> {
  return _begin;
}

template <typename T> auto input_range<T>::end() -> input_iterator<T> {
  return _end;
}

} // namespace magma

#endif // MAGMA_CORE_RANGE_H

