#include <iostream>
#include <memory>

class Computer
{
  public:
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
    ComputerFacade(std::shared_ptr<Computer> computer)
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
    std::shared_ptr<Computer> computer_;
};

int main()
{
  std::shared_ptr<Computer> computer = std::make_shared<Computer>();
  ComputerFacade facade(computer);

  facade.turnOn();
  // Output:
  // Beep!
  // Loading...
  // Ready to use!

  facade.turnOff();
  // Output:
  // Closing all programs!
  // Zzz

  return 0;
}
