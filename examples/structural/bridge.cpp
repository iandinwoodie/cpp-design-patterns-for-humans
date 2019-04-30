#include <string>
#include <iostream>
#include <memory>

class Theme
{
  public:
    typedef std::shared_ptr<Theme> ptr_t;
    virtual std::string getColor(void) = 0;
};

class WebPage
{
  public:
    virtual std::string getContent(void) = 0;
};

class About : public WebPage
{
  public:
    About(Theme::ptr_t theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "About page in " + theme_->getColor();
    }

  private:
    Theme::ptr_t theme_;
};

class Projects : public WebPage
{
  public:
    Projects(Theme::ptr_t theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "Projects page in " + theme_->getColor();
    }

  private:
    Theme::ptr_t theme_;
};


class Careers : public WebPage
{
  public:
    Careers(Theme::ptr_t theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "Careers page in " + theme_->getColor();
    }

  private:
    Theme::ptr_t theme_;
};

class DarkTheme : public Theme
{
  public:
    std::string getColor(void)
    {
      return "dark palette";
    }
};

class LightTheme : public Theme
{
  public:
    std::string getColor(void)
    {
      return "light palette";
    }
};

class AquaTheme : public Theme
{
  public:
    std::string getColor(void)
    {
      return "aqua palette";
    }
};

int main()
{
  Theme::ptr_t darkTheme = std::make_shared<DarkTheme>();
  About about(darkTheme);
  Careers careers(darkTheme);

  // Output: About page in dark palette
  std::cout << about.getContent() << std::endl;
  // Output: Careers page in dark palette
  std::cout << careers.getContent() << std::endl;

  return 0;
}
