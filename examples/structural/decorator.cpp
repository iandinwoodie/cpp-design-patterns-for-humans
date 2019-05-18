#include <iostream>
#include <memory>
#include <string>

class Coffee
{
  public:
    virtual float getPrice(void) = 0;
    virtual std::string getDescription(void) = 0;
};

class SimpleCoffee : public Coffee
{
  public:
    float getPrice(void)
    {
      return 3;
    }

    std::string getDescription(void)
    {
      return "Simple coffee";
    }
};

class MilkCoffee : public Coffee
{
  public:
    MilkCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 0.5;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", milk";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

class WhipCoffee : public Coffee
{
  public:
    WhipCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 2;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", whip";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

class VanillaCoffee : public Coffee
{
  public:
    VanillaCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 1;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", vanilla";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

int main()
{
  std::shared_ptr<Coffee> simple = std::make_shared<SimpleCoffee>();
  // Output: 3
  std::cout << simple->getPrice() << std::endl;
  // Output: Simple coffee
  std::cout << simple->getDescription() << std::endl;

  std::shared_ptr<Coffee> milk = std::make_shared<MilkCoffee>(simple);
  // Output: 3.5
  std::cout << milk->getPrice() << std::endl;
  // Output: Simple coffee, milk
  std::cout << milk->getDescription() << std::endl;

  std::shared_ptr<Coffee> whip = std::make_shared<WhipCoffee>(milk);
  // Output: 5.5
  std::cout << whip->getPrice() << std::endl;
  // Output: Simple coffee, milk, whip
  std::cout << whip->getDescription() << std::endl;

  std::shared_ptr<Coffee> vanilla = std::make_shared<VanillaCoffee>(whip);
  // Output: 6.5
  std::cout << vanilla->getPrice() << std::endl;
  // Output: Simple coffee, milk, whip, vanilla
  std::cout << vanilla->getDescription() << std::endl;
}
