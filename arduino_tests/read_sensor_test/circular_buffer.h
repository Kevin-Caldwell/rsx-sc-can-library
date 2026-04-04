#pragma once

#include <inttypes.h>

#define WRAP(val) ((val) & (kMask))

template<class T, uint32_t N = 32>
class CircularBuffer {
public:
  CircularBuffer()
  {
    static_assert((N & (N-1)) == 0 && "N should be a power of 2");
    head_ = 0;
    tail_ = 0;
  }

  ~CircularBuffer()
  {
  }

  inline void push(const T& val)
  {
    buffer_[WRAP(head_++)] = val;
  }

  inline T& pop()
  {
    return buffer_[WRAP(tail_++)];
  }

  inline T& operator[](const int index)
  {
    return buffer_[WRAP(tail_ + index)];
  }

  inline T& operator[](const int index) const
  {
    return buffer_[WRAP(tail_ + index)];
  }

  inline int elements() const
  {
    return tail_ - head_ + 1;
  }

  inline bool empty() const
  {
    return head_ == tail_;
  }

private:
  const uint32_t kMask = N - 1;
  uint32_t head_;
  uint32_t tail_;
  T buffer_[N];
};

