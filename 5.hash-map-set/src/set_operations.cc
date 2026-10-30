#include <iostream>
#include <unordered_set>
using namespace std;

unordered_set<string> unionOf(unordered_set<string> &a,
                              unordered_set<string> &b) {
  if (a.size() < b.size()) {
    swap(a, b);
  }
  unordered_set<string> result(a.begin(), a.end());

  for (auto &item : b) {
    if (result.count(item) == 0) {
      result.insert(item);
    }
  }

  return result;
}

unordered_set<string> intersectOf(unordered_set<string> &a,
                                  unordered_set<string> &b) {
  if (a.size() < b.size()) {
    swap(a, b);
  }
  unordered_set<string> result;

  for (auto &item : b) {
    if (a.count(item) != 0) {
      result.insert(item);
    }
  }

  return result;
}

unordered_set<string> differenceOf(unordered_set<string> &a,
                                   unordered_set<string> &b) {
  unordered_set<string> result;

  for (auto &item : a) {
    if (b.count(item) == 0) {
      result.insert(item);
    }
  }

  return result;
}

void printSet(const unordered_set<string> &s) {
  cout << "{ ";
  for (const auto &item : s) {
    cout << item << " ";
  }
  cout << "}" << endl;
}

int main() {
  unordered_set<string> A = {"apple", "banana", "orange", "mango"};
  unordered_set<string> B = {"banana", "orange", "grape"};

  cout << "Tap A: ";
  printSet(A);

  cout << "Tap B: ";
  printSet(B);

  cout << "\nUnion (A, B): ";
  printSet(unionOf(A, B));

  cout << "Intersection (A, B): ";
  printSet(intersectOf(A, B));

  cout << "Difference (A - B): ";
  printSet(differenceOf(A, B));

  cout << "Difference (B - A): ";
  printSet(differenceOf(B, A));

  return 0;
}
