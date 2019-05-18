#include <iostream>
#include <memory>

class Lion
{
  public:
    virtual void roar(void) = 0;
};

class AfricanLion : public Lion
{
  public:
    void roar(void)
    {
      std::cout << "*African lion roar*" << std::endl;
    }
};

class AsianLion : public Lion
{
  public:
    void roar(void)
    {
      std::cout << "*Asian lion roar*" << std::endl;
    }
};

class Hunter
{
  public:
    void hunt(Lion& lion)
    {
      lion.roar();
    }
};

class WildDog
{
  public:
    void bark(void)
    {
      std::cout << "*wild dog bark*" << std::endl;
    }
};

class WildDogAdapter : public Lion
{
  public:
    WildDogAdapter(std::shared_ptr<WildDog> dog)
        : dog_(dog)
    {
    }

    void roar(void)
    {
      dog_->bark();
    }

  private:
    std::shared_ptr<WildDog> dog_;
};

int main()
{
  std::shared_ptr<WildDog> wildDog = std::make_shared<WildDog>();
  WildDogAdapter wildDogAdapter(wildDog);

  Hunter hunter;
  hunter.hunt(wildDogAdapter); // Output: *wild dog bark*

  return 0;
}
