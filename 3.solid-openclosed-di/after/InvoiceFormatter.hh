#ifndef INVOICE_FORMATTER_HH
#define INVOICE_FORMATTER_HH

#include "Order.hh"
#include <string>

class InvoiceFormatter {
public:
  std::string format(const Order &order) const {
    auto items = order.get_items();
    std::string result = "";
    // Header
    result += "Name\tPrice\tQuantity\n";

    for (auto [name, price, quantity] : items) {
      result += name + "\t" + std::to_string(price) + "\t" +
                std::to_string(quantity) + "\n";
    }

    result += "Total\t\t\t" + std::to_string(order.total());

    return result;
  }
};

#endif // INVOICE_FORMATTER_HH
