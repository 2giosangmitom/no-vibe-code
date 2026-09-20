#include "vec.hh"
#include <cassert>
#include <iostream>
#include <string>

int main() {
  Vec<std::string> v;
  assert(v.empty());
  assert(v.size() == 0);
  assert(v.capacity() == 0);

  v.push_back("apple");
  v.push_back("banana");
  v.push_back("cherry");

  assert(!v.empty());
  assert(v.size() == 3);
  assert(v.capacity() >= 3);

  assert(v[0] == "apple");
  assert(v[1] == "banana");
  assert(v.at(2) == "cherry");

  try {
    v.at(3);
    assert(false);
  } catch (const std::out_of_range &e) {
    // Expected exception
  }

  v.insert(1, "blueberry");
  assert(v.size() == 4);
  assert(v[0] == "apple");
  assert(v[1] == "blueberry");
  assert(v[2] == "banana");
  assert(v[3] == "cherry");

  v.insert(0, "avocado");
  assert(v.size() == 5);
  assert(v[0] == "avocado");

  v.insert(v.size(), "date");
  assert(v.size() == 6);
  assert(v[5] == "date");

  v.erase(0);
  assert(v.size() == 5);
  assert(v[0] == "apple");

  v.erase(1);
  assert(v.size() == 4);
  assert(v[1] == "banana");

  std::string popped = v.pop_back();
  assert(popped == "date");
  assert(v.size() == 3);
  assert(v[2] == "cherry");

  std::string expected[] = {"apple", "banana", "cherry"};
  size_t idx = 0;
  for (const auto &item : v) {
    assert(item == expected[idx]);
    ++idx;
  }
  assert(idx == 3);

  Vec<std::string> copy = v;
  assert(copy.size() == v.size());
  assert(copy[0] == "apple");

  copy[0] = "apricot";
  assert(v[0] == "apple");
  assert(copy[0] == "apricot");

  Vec<std::string> assigned;
  assigned = v;
  assert(assigned.size() == v.size());
  assert(assigned[1] == "banana");

  Vec<std::string> moved = std::move(copy);
  assert(moved.size() == 3);
  assert(moved[0] == "apricot");
  assert(copy.empty());

  std::cout << "All tests passed successfully!" << std::endl;
}
