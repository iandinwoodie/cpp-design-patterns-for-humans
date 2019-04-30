#include <assert.h>

class President
{
  public:
    static President& getInstance()
    {
      static President instance;
      return instance;
    }

  private:
    President()
    {
    }

    ~President()
    {
    }
};

int main()
{
  President& president1 = President::getInstance();
  President& president2 = President::getInstance();

  // There can only be 1 president, so they must be the same.
  assert(&president1 == &president2);

  return 0;
}
