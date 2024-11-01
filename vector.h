#pragma once
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>

template <typename T> class Vector {
public:
  Vector() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
  }

  explicit Vector(size_t sz) {
    capacity_ = sz;
    size_ = sz;
    if (capacity_ == 0) {
      data_ = nullptr;
    } else {
      data_ = std::make_unique<T[]>(capacity_);
    }
    for (size_t i = 0; i < size_; i++) {
      data_[i] = T();
    }
  }

  Vector(std::initializer_list<T> list) {
    capacity_ = list.size();
    size_ = list.size();
    if (capacity_ == 0) {
      data_ = nullptr;
    } else {
      data_ = std::make_unique<T[]>(capacity_);
    }
    size_t i = 0;
    for (auto &r : list) {
      data_[i++] = r;
    }
  }

  Vector(const Vector &a) {
    capacity_ = a.capacity_;
    size_ = a.size_;
    if (capacity_ == 0) {
      data_ = nullptr;
    } else {
      data_ = std::make_unique<T[]>(capacity_);
    }
    for (size_t i = 0; i < size_; i++) {
      data_[i] = a.data_[i];
    }
  }

  Vector(Vector &&a) {
    capacity_ = a.capacity_;
    size_ = a.size_;
    data_ = a.data_;
    a.data_ = nullptr;
  }

  ~Vector() { data_ = nullptr; }

  Vector &operator=(Vector a) {
    Swap(a);
    return *this;
  }

  size_t Size() const { return size_; }

  size_t Capacity() const { return capacity_; }

  void PushBack(const T &a) {
    if (size_ == capacity_) {
      capacity_ *= 2;
      if (capacity_ == 0) {
        capacity_++;
      }
      std::unique_ptr<T[]> u = std::make_unique<T[]>(capacity_);
      for (size_t i = 0; i < size_; i++) {
        u[i] = data_[i];
      }
      data_ = std::move(u);
    }
    data_[size_] = a;
    size_++;
  }

  void PopBack() { size_--; }

  void Clear() { size_ = 0; }

  void Reserve(size_t capacity) {
    if (capacity <= capacity_)
      return;
    capacity_ = capacity;
    std::unique_ptr<T[]> u = std::make_unique<T[]>(capacity_);
    for (int i = 0; i < size_; i++) {
      u[i] = data_[i];
    }
    data_ = std::move(u);
  }

  void Swap(Vector &rhs) {
    std::swap(capacity_, rhs.capacity_);
    std::swap(size_, rhs.size_);
    std::swap(data_, rhs.data_);
  }

  T &operator[](size_t ind) { return data_[ind]; }

  T operator[](size_t ind) const { return data_[ind]; }

private:
  std::unique_ptr<T[]> data_;
  size_t capacity_;
  size_t size_;
};
