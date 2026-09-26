#ifndef EMAIL_SENDER_HH
#define EMAIL_SENDER_HH

#include <iostream>
#include <string>

class EmailSender {
public:
  void send(const std::string &to, const std::string &body) {
    std::cout << "Sending email to " + to + "\n" << "Body: \n" + body;
  }
};

#endif // EMAIL_SENDER_HH
