#include <iostream>
#include <memory>

class Interviewer
{
  public:
    typedef std::shared_ptr<Interviewer> ptr_t;
    virtual void askQuestions(void) = 0;
};

class Developer : public Interviewer
{
  public:
    void askQuestions(void)
    {
      std::cout << "Asking about design patterns!" << std::endl;
    }
};

class CommunityExecutive : public Interviewer
{
  public:
    void askQuestions(void)
    {
      std::cout << "Asking about community building!" << std::endl;
    }
};

class HiringManager
{
  public:
    void takeInterview(void)
    {
      Interviewer::ptr_t interviewer = makeInterviewer();
      interviewer->askQuestions();
    }

  protected:
    virtual Interviewer::ptr_t makeInterviewer(void) = 0;
};

class DevelopmentManager : public HiringManager
{
  protected:
    Interviewer::ptr_t makeInterviewer(void)
    {
      return std::make_shared<Developer>();
    }
};

class MarketingManager : public HiringManager
{
  protected:
    Interviewer::ptr_t makeInterviewer(void)
    {
      return std::make_shared<CommunityExecutive>();
    }
};

int main()
{
  DevelopmentManager developmentManager = DevelopmentManager();
  developmentManager.takeInterview(); // Output: Asking about design patterns!

  MarketingManager marketingManager = MarketingManager();
  marketingManager.takeInterview(); // Output: Asking about community building!

  return 0;
}
