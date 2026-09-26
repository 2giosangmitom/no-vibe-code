#ifndef DISCOUNT_HH
#define DISCOUNT_HH

class DiscountPolicy {
public:
  virtual double apply(double total) const = 0;
  virtual ~DiscountPolicy() = default;
};

class NoDisCount : public DiscountPolicy {
public:
  double apply(double total) const override { return total; }
};

class PercentDiscount : public DiscountPolicy {
private:
  double rate;

public:
  PercentDiscount(double rate) : rate{rate} {}
  double apply(double total) const override { return total - total * rate; }
};

class FixedDiscount : public DiscountPolicy {
private:
  double amount, minTotal;

public:
  FixedDiscount(double amount, double minTotal)
      : amount{amount}, minTotal{minTotal} {}

  double apply(double total) const override {
    if (total < minTotal)
      return total;
    return total - amount;
  }
};

#endif // DISCOUNT_HH
