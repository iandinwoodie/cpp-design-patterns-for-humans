#include <iostream>
#include <memory>

class BurgerBuilder;

class Burger
{
  public:
    typedef std::shared_ptr<Burger> ptr_t;
    Burger(BurgerBuilder* builder);
    void getDescription(void);

  private:
    int patties_;
    bool cheese_;
    bool pepperoni_;
    bool lettuce_;
    bool tomato_;
};

class BurgerBuilder
{
  public:
    BurgerBuilder(int patties)
        : patties(patties), cheese(false), pepperoni(false), lettuce(false),
          tomato(false)
    {
    }

    BurgerBuilder& addCheese(void)
    {
      cheese = true;
      return (*this);
    }

    BurgerBuilder& addPepperoni(void)
    {
      pepperoni = true;
      return (*this);
    }

    BurgerBuilder& addLettuce(void)
    {
      lettuce = true;
      return (*this);
    }

    BurgerBuilder& addTomato(void)
    {
      tomato = true;
      return (*this);
    }

    Burger::ptr_t build(void)
    {
      Burger::ptr_t burger(new Burger(this));
      return burger;
    }

    int patties;
    bool cheese;
    bool pepperoni;
    bool lettuce;
    bool tomato;
};

Burger::Burger(BurgerBuilder* builder)
    : patties_(builder->patties), cheese_(builder->cheese),
      pepperoni_(builder->pepperoni), lettuce_(builder->lettuce),
      tomato_(builder->tomato)
{
}

void Burger::getDescription(void)
{
  std::cout << patties_ << " patties";
  if (cheese_) {
    std::cout << ", cheese";
  }
  if (pepperoni_) {
    std::cout << ", pepperoni";
  }
  if (lettuce_){
    std::cout << ", lettuce";
  }
  if (tomato_) {
    std::cout << ", tomato";
  }
  std::cout << std::endl;
}

int main()
{
  // One double patty burger with no dairy.
  Burger::ptr_t burger = BurgerBuilder(2).
      addPepperoni().
      addLettuce().
      addTomato().
      build();
  // Output: 2 patties, pepperoni, lettuce, tomato
  burger->getDescription();

  // One triple patty buger with everything.
  Burger::ptr_t burger2 = BurgerBuilder(3).
      addPepperoni().
      addCheese().
      addLettuce().
      addTomato().
      build();
  // Output: 3 patties, cheese, pepperoni, lettuce, tomato
  burger2->getDescription();

  return 0;
}