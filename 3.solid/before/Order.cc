#include <string>

class Order {
public:
  void addItem(std::string name, double price, int qty);
  double total() const;                  // tính tiền
  std::string toInvoiceText() const;     // định dạng hóa đơn
  void saveToFile(const std::string &p); // ghi file
  void sendEmail(const std::string &to); // gửi email (chỉ in ra console)
};
