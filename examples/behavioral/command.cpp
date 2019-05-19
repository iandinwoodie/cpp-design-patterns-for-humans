#include <iostream>
#include <memory>

// The receiver.
class Bulb
{
  public:
    void turnOn(void)
    {
      std::cout << "Bulb has been lit." << std::endl;
    }

    void turnOff(void)
    {
      std::cout << "Darkness!" << std::endl;
    }
};

class Command
{
  public:
    virtual void execute(void) = 0;
    virtual void undo(void) = 0;
    virtual void redo(void) = 0;
};

// A command.
class TurnOn : public Command
{
  public:
    TurnOn(std::shared_ptr<Bulb> bulb)
        : bulb_(bulb)
    {
    }

    void execute(void)
    {
      bulb_->turnOn();
    }

    void undo(void)
    {
      bulb_->turnOff();
    }

    void redo(void)
    {
      execute();
    }

  private:
    std::shared_ptr<Bulb> bulb_;
};

// Another command.
class TurnOff : public Command
{
  public:
    TurnOff(std::shared_ptr<Bulb> bulb)
        : bulb_(bulb)
    {
    }

    void execute(void)
    {
      bulb_->turnOff();
    }

    void undo(void)
    {
      bulb_->turnOn();
    }

    void redo(void)
    {
      execute();
    }

  private:
    std::shared_ptr<Bulb> bulb_;
};

// The invoker.
class RemoteControl
{
  public:
    void submit(std::shared_ptr<Command> command)
    {
      command->execute();
    }
};

int main()
{
  std::shared_ptr<Bulb> bulb = std::make_shared<Bulb>();

  std::shared_ptr<TurnOn> turnOn = std::make_shared<TurnOn>(bulb);
  std::shared_ptr<TurnOff> turnOff = std::make_shared<TurnOff>(bulb);

  RemoteControl remote;
  remote.submit(turnOn);
  remote.submit(turnOff);
  // Output:
  // Bulb has been lit.
  // Darkness!

  return 0;
}
