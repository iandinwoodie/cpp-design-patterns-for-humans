#include <iostream>
#include <memory>

class Door
{
  public:
    typedef std::shared_ptr<Door> ptr_t;
    virtual float getWidth(void) = 0;
    virtual float getHeight(void) = 0;
};

class WoodenDoor : public Door
{
  public:
    WoodenDoor(float width, float height)
        : width_(width), height_(height)
    {
    }

    float getWidth(void)
    {
      return width_;
    }

    float getHeight(void)
    {
      return height_;
    }

  private:
    float width_;
    float height_;
};

class DoorFactory
{
  public:
    static Door::ptr_t makeDoor(float width, float height)
    {
      return std::make_shared<WoodenDoor>(width, height);
    }
};

int main()
{
  // Make a door with dimensions 100x200.
  Door::ptr_t door = DoorFactory::makeDoor(100, 200);

  // Output: width = 100
  std::cout << "width = " << door->getWidth() << std::endl;
  // Output: height = 200
  std::cout << "height = " << door->getHeight() << std::endl;

  // We can use the factory again to make a door with dimensions 50x100.
  Door::ptr_t door2 = DoorFactory::makeDoor(50, 100);

  // Output: width = 50
  std::cout << "width = " << door2->getWidth() << std::endl;
  // Output: height = 100
  std::cout << "height = " << door2->getHeight() << std::endl;

  return 0;
}
