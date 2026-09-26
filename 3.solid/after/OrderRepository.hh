#ifndef ORDER_REPOSITORY_HH
#define ORDER_REPOSITORY_HH

#include "InvoiceFormatter.hh"
#include "Order.hh"
#include <fstream>

class OrderRepository {
private:
  InvoiceFormatter invoice_formatter;

public:
  OrderRepository(InvoiceFormatter &invoice_fmt)
      : invoice_formatter{invoice_fmt} {}

  void save(const Order &order, const std::string &path) {
    std::fstream fs(path);

    fs << invoice_formatter.format(order);

    fs.close();
  }
};

#endif // ORDER_REPOSITORY_HH
