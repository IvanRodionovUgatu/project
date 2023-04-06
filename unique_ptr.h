#ifndef _UNIQUE_PTR_H_
#define _UNIQUE_PTR_H_

#include <iostream>

template <typename T>
class UniquePtr {
 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  }
  UniquePtr(const UniquePtr<T>& other) = delete;
  UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;

  UniquePtr(UniquePtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T* Release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }

  void Reset(T* ptr = nullptr) {
    T* temp = ptr_;
    ptr_ = ptr;
    delete temp;
  }

  void Swap(UniquePtr<T>& other) {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  ~UniquePtr() {
    delete ptr_;
  }

 private:
  T* ptr_;
};

#endif