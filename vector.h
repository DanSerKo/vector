#pragma once
#include <cstddef>
#include <iterator>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector() {
        size_ = 0;
        capacity_ = 1;
        x_ = new T[capacity_];
    }

    explicit Vector(size_t sz) {
        capacity_ = sz;
        size_ = sz;
        x_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            x_[i] = T();
        }
    }

    Vector(std::initializer_list<T>&& list) {
        capacity_ = list.size();
        size_ = list.size();
        x_ = new T[capacity_];
        size_t i = 0;
        for (auto& item : list) {
            x_[i++] = std::move(item);
        }
    }

    Vector(const Vector& a) {
        capacity_ = a.capacity_;
        size_ = a.size_;
        x_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            x_[i] = a.x_[i];
        }
    }

    Vector(Vector&& a) {
        capacity_ = a.capacity_;
        size_ = a.size_;
        x_ = a.x_;
        a.x_ = nullptr;
    }

    ~Vector() {
        if (x_ != nullptr) {
            delete[] x_;
        }
        x_ = nullptr;
    }

    Vector& operator= (Vector a) {
        Swap(a);
        return *this;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T& a) {
        if (size_ == capacity_) {
            Reserve(capacity_ * 2);
        }
        x_[size_++] = a;
    }

    void PopBack() {
        size_--;
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t capacity) {
        if (capacity <= capacity_)
            return;
        capacity_ = capacity;
        T* u = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            u[i] = std::move(x_[i]);
        }
        if (x_ != nullptr) {
            delete[] x_;
        }
        x_ = std::move(u);
    }

    void Swap(Vector& rhs) {
        std::swap(capacity_, rhs.capacity_);
        std::swap(size_, rhs.size_);
        std::swap(x_, rhs.x_);
    }

    T& operator[](size_t ind) {
        return x_[ind];
    }

    T operator[](size_t ind) const {
        return x_[ind];
    }

private:
    T* x_;
    size_t capacity_;
    size_t size_;
};
