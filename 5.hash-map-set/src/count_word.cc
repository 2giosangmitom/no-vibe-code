#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void trim(std::string &text) {
  int i = 0;
  int n = text.size();
  while (i < n && !isalpha(text[i])) {
    ++i;
  }

  int j = n - 1;
  while (j >= 0 && !isalpha(text[j])) {
    --j;
  }

  text = text.substr(i, j - i + 1);
}

std::vector<std::string> tokenize(const std::string &text) {
  size_t i = 0;
  size_t j = 0;
  size_t n = text.size();
  std::vector<std::string> res;

  while (j < n) {
    if (!isalpha(text[j])) {
      auto tmp = text.substr(i, j - i);
      trim(tmp);
      if (!tmp.empty()) {
        std::transform(tmp.begin(), tmp.end(), tmp.begin(),
                       [](char c) { return tolower(c); });
        res.push_back(tmp);
      }
      i = j;
    }
    ++j;
  }

  return res;
}

std::unordered_map<std::string, int> countWords(const std::string &text) {
  auto tokens = tokenize(text);
  std::unordered_map<std::string, int> result;

  for (auto &token : tokens) {
    ++result[token];
  }

  return result;
}

std::vector<std::pair<std::string, int>>
topK(std::unordered_map<std::string, int> map, int k) {
  std::vector<std::pair<std::string, int>> result;

  for (auto &[k, v] : map) {
    result.push_back(std::pair<std::string, int>(k, v));
  }
  std::sort(result.begin(), result.end(),
            [](std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
              if (a.second == b.second)
                return a.first < b.first;
              return a.second > b.second;
            });

  int n = result.size();
  while (n > k) {
    result.pop_back();
    n--;
  }

  return result;
}

size_t distinctWords(const std::string &text) {
  std::unordered_set<std::string> set;
  auto tokens = tokenize(text);

  for (auto &word : tokens) {
    set.insert(word);
  }

  return set.size();
}

int main() {
  auto tokens = tokenize("An an AN, binh. Binh!");
  std::cout << tokens.size() << std::endl;
  for (auto token : tokens) {
    std::cout << token << std::endl;
  }

  auto freq =
      countWords("An AN an, Binh Binh, Chien, Duy Duy, Hieu hieu Hieu hieU!");
  for (auto &[k, v] : freq) {
    std::cout << k << ": " << v << std::endl;
  }

  auto top3 = topK(freq, 3);
  for (auto &[k, v] : top3) {
    std::cout << k << ": " << v << std::endl;
  }

  std::cout << distinctWords(
      "An AN an, Binh Binh, Chien, Duy Duy, Hieu hieu Hieu hieU!");
}
