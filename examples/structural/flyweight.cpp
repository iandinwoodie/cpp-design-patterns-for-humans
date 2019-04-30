#include <iostream>
#include <memory>
#include <unordered_map>

class Tea
{
  public:
    typedef std::shared_ptr<Tea> ptr_t;
};

class TeaMaker
{
  public:
    typedef std::shared_ptr<TeaMaker> ptr_t;

    Tea::ptr_t make(const std::string& preference)
    {
      auto match = availableTea_.find(preference);
      if (match == availableTea_.end()) {
        availableTea_[preference] = std::make_shared<Tea>();
      }

      return availableTea_[preference];
    }

    int getPreferenceCount(void)
    {
      return availableTea_.size();
    }

  private:
    std::unordered_map<std::string, Tea::ptr_t> availableTea_;
};

class TeaShop
{
  public:
    TeaShop(TeaMaker::ptr_t maker)
        : maker_(maker)
    {
    }

    void takeOrder(const std::string& preference, int table)
    {
      orders_[table] = maker_->make(preference);
    }

    void serve(void)
    {
      for (auto order : orders_) {
        std::cout << "Serving tea to table " << order.first << std::endl;
      }
    }

    int getPreferenceCount(void)
    {
      return maker_->getPreferenceCount();
    }

  private:
    TeaMaker::ptr_t maker_;
    std::unordered_map<int, Tea::ptr_t> orders_;
};

int main()
{
  TeaMaker::ptr_t maker = std::make_shared<TeaMaker>();
  TeaShop shop(maker);

  // No orders have been taken, so there are no available teas.
  std::cout << shop.getPreferenceCount() << std::endl; // Output: 0

  // Take some orders.
  shop.takeOrder("half sugar", 1);
  shop.takeOrder("with milk", 2);
  shop.takeOrder("with boba", 5);

  // We create a new batch of tea for each preference.
  std::cout << shop.getPreferenceCount() << std::endl; // Output: 3

  // Take an order with a previously requested preference.
  shop.takeOrder("half sugar", 4);

  // Since we have some tea from the last time this request was made, no new
  // batch was created.
  std::cout << shop.getPreferenceCount() << std::endl; // Output: 3

  // Serve the customers.
  shop.serve(); 

  return 0;
}
