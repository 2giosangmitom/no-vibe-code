#ifndef ORDER_HH
#define ORDER_HH

#include <string>
#include <tuple>
#include <vector>

class Order {
private:
  std::vector<std::tuple<std::string, double, int>> items;

public:
  auto get_items() const {
    return items;
  }

  double total() const {
    double sum = 0.0;

    for (auto [name, price, quantity] : items) {
      sum += price * quantity;
    }

    return sum;
  }
};

#endif // ORDER_HH
