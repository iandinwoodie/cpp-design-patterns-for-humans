#include <iostream>
#include <memory>

class Door
{
  public:
    typedef std::shared_ptr<Door> ptr_t;
    virtual void getDescription(void) = 0;
};

class WoodenDoor : public Door
{
  public:
    void getDescription(void)
    {
      std::cout << "I am a wooden door." << std::endl;
    }
};

class IronDoor : public Door
{
  public:
    void getDescription(void)
    {
      std::cout << "I am an iron door." << std::endl;
    }
};

class DoorFittingExpert
{
  public:
    typedef std::shared_ptr<DoorFittingExpert> ptr_t;
    virtual void getDescription(void) = 0;
};

class Welder : public DoorFittingExpert
{
  public:
    void getDescription(void)
    {
      std::cout << "I can only fit iron doors." << std::endl;
    }
};

class Carpenter : public DoorFittingExpert
{
  public:
    void getDescription(void)
    {
      std::cout << "I can only fit wooden doors." << std::endl;

    }
};

class DoorFactory
{
  public:
    virtual Door::ptr_t makeDoor(void) = 0;
    virtual DoorFittingExpert::ptr_t makeFittingExpert(void) = 0;
};

class WoodenDoorFactory : public DoorFactory
{
  public:
    Door::ptr_t makeDoor(void)
    {
      return std::make_shared<WoodenDoor>();
    }

    DoorFittingExpert::ptr_t makeFittingExpert(void)
    {
      return std::make_shared<Carpenter>();
    }
};

class IronDoorFactory : public DoorFactory
{
  public:
    Door::ptr_t makeDoor(void)
    {
      return std::make_shared<IronDoor>();
    }

    DoorFittingExpert::ptr_t makeFittingExpert(void)
    {
      return std::make_shared<Welder>();
    }
};

int main()
{
  WoodenDoorFactory woodenFactory = WoodenDoorFactory();
  Door::ptr_t door = woodenFactory.makeDoor();
  DoorFittingExpert::ptr_t expert = woodenFactory.makeFittingExpert();

  door->getDescription(); // Output: I am a wooden door.
  expert->getDescription(); // Output: I can only fit wooden doors.

  IronDoorFactory ironFactory = IronDoorFactory();
  Door::ptr_t door2 = ironFactory.makeDoor();
  DoorFittingExpert::ptr_t expert2 = woodenFactory.makeFittingExpert();

  door2->getDescription(); // Output: I am an iron door.
  expert2->getDescription(); // Output: I can only fit iron doors.

  return 0;
}
