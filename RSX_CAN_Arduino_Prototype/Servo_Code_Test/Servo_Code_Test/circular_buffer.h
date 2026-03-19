#pragma once

#include <inttypes.h>

#define WRAP(val) ((val) & (kMask))

template<class T, uint32_t N = 32>
class CircularBuffer {
public:
  CircularBuffer()
  : head_(0x0)
  {
    static_assert((N & (N-1)) == 0);
  }

  ~CircularBuffer()
  {
  }

  void push(const T& val)
  {
    buffer_[WRAP(head_++)] = val;
  }

  T& pop()
  {
    return buffer_[WRAP(head_--)];
  }

  T& operator[](int index)
  {
    return buffer_[WRAP(head_ - index)];
  }

  T& operator[](int index) const
  {
    return buffer_[WRAP(head_ - index)];
  }

private:
  constexpr uint32_t kMask = N - 1;
  uint32_t head_;
  T buffer_[N];
};
