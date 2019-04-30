#include <iostream>
#include <string>

class Sheep
{
  public:
    Sheep(const std::string& name, const std::string& category)
        : name_(name), category_(category)
    {
    }

    void setName(const std::string name)
    {
      name_ = name;
    }

    std::string getName(void)
    {
      return name_;
    }

    void setCategory(const std::string category)
    {
      category_ = category;
    }

    std::string getCategory(void)
    {
      return category_;
    }

  private:
    std::string name_;
    std::string category_;
};

int main()
{
  Sheep original = Sheep("Molly", "Mountain Sheep");
  std::cout << original.getName() << std::endl; // Output: Molly
  std::cout << original.getCategory() << std::endl; // Output: Mountain Sheep

  Sheep clone = original;
  clone.setName("Dolly");
  std::cout << clone.getName() << std::endl; // Output: Dolly
  std::cout << clone.getCategory() << std::endl; // Output: Mountain Sheep

  return 0;
}
