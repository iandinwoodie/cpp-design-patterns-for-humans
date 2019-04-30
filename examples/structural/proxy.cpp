#include <iostream>
#include <memory>
#include <string>

class Door
{
  public:
    typedef std::shared_ptr<Door> ptr_t;
    virtual void open(void) = 0;
    virtual void close(void) = 0;
};

class LabDoor : public Door
{
  public:
    void open(void)
    {
      std::cout << "Opening lab door" << std::endl;
    }

    void close(void)
    {
      std::cout << "Closing lab door" << std::endl;
    }
};

class SecuredDoor
{
  public:
    SecuredDoor(Door::ptr_t door)
        : door_(door)
    {
    }

    void open(const std::string& password)
    {
      if (authenticate(password)) {
        door_->open();
      } else {
        std::cout << "No way, Jose!" << std::endl;
      }
    }

    void close(void)
    {
      door_->close();
    }

  private:
    bool authenticate(const std::string& password)
    {
      return password == "Bond007";
    }

    Door::ptr_t door_;
};

int main()
{
  Door::ptr_t labDoor = std::make_shared<LabDoor>();
  SecuredDoor securedDoor(labDoor);

  securedDoor.open("invalid"); // Output: No way, Jose!
  securedDoor.open("Bond007"); // Output: Opening lab door
  securedDoor.close(); // Output: Closing lab door

  return 0;
}
