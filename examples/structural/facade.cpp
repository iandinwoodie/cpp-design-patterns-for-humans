#include <iostream>
#include <memory>

class Computer
{
  public:
    typedef std::shared_ptr<Computer> ptr_t;

    void makeBootSound(void)
    {
      std::cout << "Beep!" << std::endl;
    }

    void showLoadingScreen(void)
    {
      std::cout << "Loading..." << std::endl;
    }

    void showWelcomeScreen(void)
    {
      std::cout << "Ready to use!" << std::endl;
    }

    void closeEverything(void)
    {
      std::cout << "Closing all programs!" << std::endl;
    }
    void sleep(void)
    {
      std::cout << "Zzz" << std::endl;
    }
};

class ComputerFacade
{
  public:
    ComputerFacade(Computer::ptr_t computer)
        : computer_(computer)
    {
    }

    void turnOn(void)
    {
      computer_->makeBootSound();
      computer_->showLoadingScreen();
      computer_->showWelcomeScreen();
    }

    void turnOff(void)
    {
      computer_->closeEverything();
      computer_->sleep();
    }

  private:
    Computer::ptr_t computer_;
};

int main()
{
  Computer::ptr_t computer = std::make_shared<Computer>();
  ComputerFacade facade(computer);

  // Output:
  // Beep!
  // Loading...
  // Ready to use!
  facade.turnOn();

  // Output:
  // Closing all programs!
  // Zzz
  facade.turnOff();

  return 0;
}
