#ifndef VEC_HH
#define VEC_HH

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T> class Vec {
public:
  Vec() : _data{nullptr}, _size{0}, _capacity{0} {}

  explicit Vec(size_t size)
      : _data{new T[size]{}}, _size{size}, _capacity{size} {}

  Vec(const Vec &other)
      : _data{new T[other._capacity]}, _size{other._size},
        _capacity{other._capacity} {
    for (size_t i = 0; i < _size; ++i) {
      _data[i] = other._data[i];
    }
  }

  Vec(Vec &&other) noexcept
      : _data{other._data}, _size{other._size}, _capacity{other._capacity} {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }

  Vec &operator=(const Vec &other) {
    if (this != &other) {
      T *new_data = new T[other._capacity];
      for (size_t i = 0; i < other._size; ++i) {
        new_data[i] = other._data[i];
      }
      delete[] _data;
      _data = new_data;
      _size = other._size;
      _capacity = other._capacity;
    }
    return *this;
  }

  Vec &operator=(Vec &&other) noexcept {
    if (this != &other) {
      delete[] _data;
      _data = other._data;
      _size = other._size;
      _capacity = other._capacity;

      other._data = nullptr;
      other._size = 0;
      other._capacity = 0;
    }
    return *this;
  }

  ~Vec() { delete[] _data; }

  size_t size() const { return _size; }
  size_t capacity() const { return _capacity; }
  bool empty() const { return _size == 0; }

  bool reserve(size_t cap) {
    if (cap <= _capacity) {
      return true;
    }

    T *new_data = new (std::nothrow) T[cap];
    if (!new_data) {
      return false;
    }

    for (size_t i = 0; i < _size; ++i) {
      new_data[i] = std::move(_data[i]);
    }

    delete[] _data;
    _data = new_data;
    _capacity = cap;
    return true;
  }

  void push_back(const T &x) {
    if (_size == _capacity) {
      size_t new_cap = (_capacity == 0) ? 1 : _capacity * 2;
      if (!reserve(new_cap)) {
        throw std::bad_alloc();
      }
    }
    _data[_size] = x;
    ++_size;
  }

  T pop_back() {
    if (empty()) {
      throw std::out_of_range("Cannot pop_back from an empty Vec");
    }
    --_size;
    return _data[_size];
  }

  void insert(size_t i, const T &x) {
    if (i > _size) {
      throw std::out_of_range("Index out of bounds for insert");
    }
    if (_size == _capacity) {
      size_t new_cap = (_capacity == 0) ? 1 : _capacity * 2;
      if (!reserve(new_cap)) {
        throw std::bad_alloc();
      }
    }
    for (size_t j = _size; j > i; --j) {
      _data[j] = std::move(_data[j - 1]);
    }
    _data[i] = x;
    ++_size;
  }

  void erase(size_t i) {
    if (i >= _size) {
      throw std::out_of_range("Index out of bounds for erase");
    }
    for (size_t j = i; j < _size - 1; ++j) {
      _data[j] = std::move(_data[j + 1]);
    }
    --_size;
  }

  T &operator[](size_t i) { return at(i); }
  const T &operator[](size_t i) const { return at(i); }

  T &at(size_t i) {
    if (i >= _size) {
      throw std::out_of_range("Index out of bounds");
    }
    return _data[i];
  }

  const T &at(size_t i) const {
    if (i >= _size) {
      throw std::out_of_range("Index out of bounds");
    }
    return _data[i];
  }

  T *begin() { return _data; }
  T *end() { return _data + _size; }
  const T *begin() const { return _data; }
  const T *end() const { return _data + _size; }

private:
  T *_data;
  size_t _size;
  size_t _capacity;
};

#endif
