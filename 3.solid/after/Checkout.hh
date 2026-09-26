#ifndef CHECKOUT_HH
#define CHECKOUT_HH

#include "Discount.hh"
#include "Order.hh"
#include <memory>

class Checkout {
private:
  std::unique_ptr<DiscountPolicy> discount_policy;

public:
  Checkout(std::unique_ptr<DiscountPolicy> discount_policy) {
    this->discount_policy = std::move(discount_policy);
  }

  double total(const Order &order) const {
    const double init_total = order.total();
    auto discount = discount_policy.get();
    return discount->apply(init_total);
  }
};

#endif // CHECKOUT_HH
