#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class IntHashSet {
private:
  vector<vector<int>> _data;
  size_t _capacity;
  size_t _size = 0;

  size_t _hash(int x) const {
    return (static_cast<uint32_t>(x) * 2654435761u) % _capacity;
  }

  void _rehash() {
    size_t newCapacity = _capacity * 2;

    vector<vector<int>> newData(newCapacity);

    for (const auto &bucket : _data) {
      for (int x : bucket) {
        size_t h = (static_cast<uint32_t>(x) * 2654435761u) % newCapacity;

        newData[h].push_back(x);
      }
    }

    _data = std::move(newData);
    _capacity = newCapacity;
  }

public:
  IntHashSet(size_t size) : _data(size), _capacity(size) {
    if (size == 0)
      throw invalid_argument("Capacity must be positive");
  }

  bool insert(int x) {
    size_t h = _hash(x);

    for (int value : _data[h]) {
      if (value == x)
        return false;
    }

    _data[h].push_back(x);
    ++_size;

    if (loadFactor() > 0.75)
      _rehash();

    return true;
  }

  bool contains(int x) const {
    size_t h = _hash(x);

    for (int value : _data[h]) {
      if (value == x)
        return true;
    }

    return false;
  }

  bool erase(int x) {
    size_t h = _hash(x);

    auto &bucket = _data[h];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (*it == x) {
        bucket.erase(it);
        --_size;
        return true;
      }
    }

    return false;
  }

  size_t size() const { return _size; }

  double loadFactor() const { return static_cast<double>(_size) / _capacity; }
};

int main() {
  IntHashSet s(4);

  s.insert(10);
  s.insert(20);
  s.insert(30);

  cout << "Size: " << s.size() << '\n';
  cout << "Load factor: " << s.loadFactor() << '\n';

  s.insert(40);

  cout << "After rehash:\n";
  cout << "Size: " << s.size() << '\n';
  cout << "Load factor: " << s.loadFactor() << '\n';

  cout << "Contains 20: " << s.contains(20) << '\n';

  s.erase(20);

  cout << "Contains 20: " << s.contains(20) << '\n';
  cout << "Size: " << s.size() << '\n';

  return 0;
}
