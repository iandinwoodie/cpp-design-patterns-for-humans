#include <iostream>
#include <memory>
#include <string>

class Account
{
  public:
    Account(void)
        : name_("empty account"), balance_(0), successor_()
    {
    }

    void setNext(std::shared_ptr<Account> account)
    {
      successor_ = account;
    }

    void pay(float amount)
    {
      if (canPay(amount)) {
        std::cout << "Paid " << amount << " using " << name_ << "."
                  << std::endl;
        balance_ -= amount;
      } else if (successor_) {
        std::cout << "Cannot pay using " << name_ << ". Proceeding ..."
                  << std::endl;
        successor_->pay(amount);
      } else {
        std::cerr << "None of the accounts have enough balance." << std::endl;
      }
    }

    bool canPay(float amount)
    {
      return balance_ >= amount;
    }

  protected:
    std::string name_;
    float balance_;
    std::shared_ptr<Account> successor_;
};

class Bank : public Account
{
  public:
    Bank(float balance)
    {
      name_ = "bank";
      balance_ = balance;
    }
};

class Paypal : public Account
{
  public:
    Paypal(float balance)
    {
      name_ = "paypal";
      balance_ = balance;
    }
};

class Bitcoin : public Account
{
  public:
    Bitcoin(float balance)
    {
      name_ = "bitcoin";
      balance_ = balance;
    }
};

int main()
{
  // We are going to create the chain: bank->paypal->bitcoin.
  
  // First, create the accounts.
  std::shared_ptr<Bank> bank = std::make_shared<Bank>(100);
  std::shared_ptr<Paypal> paypal = std::make_shared<Paypal>(200);
  std::shared_ptr<Bitcoin> bitcoin = std::make_shared<Bitcoin>(300);

  // Next, establish the order.
  bank->setNext(paypal);
  paypal->setNext(bitcoin);

  // Let's try to pay using the first priority (i.e., the bank).
  bank->pay(250);
  // Output:
  // Cannot pay using bank. Proceeding ...
  // Cannot pay using paypal. Proceeding ...
  // Paid 250 using bitcoin.

  return 0;
}
