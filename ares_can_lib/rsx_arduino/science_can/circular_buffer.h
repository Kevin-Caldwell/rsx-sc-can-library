#pragma once

#include <inttypes.h>

#define WRAP(val) ((val) & (kMask))

template<class T, uint32_t N = 16>
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

  inline int push(const T& val)
  {
    buffer_[WRAP(head_++)] = val;
    return head_ - tail_ + 1 < N;
  }

  inline T& pop()
  {
    return buffer_[WRAP(tail_++)];
  }

  inline T& last()
  {
    return buffer_[WRAP(tail_)];
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
    return head_ - tail_;
  }

  inline bool empty() const
  {
    return head_ == tail_;
  }

  inline bool full() const
  {
    return head_ - tail_ >= N;
  }

private:
  const uint32_t kMask = N - 1;
  uint32_t head_;
  uint32_t tail_;
  T buffer_[N];
};
