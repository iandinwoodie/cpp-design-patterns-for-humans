#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Employee
{
  public:
    typedef std::shared_ptr<Employee> ptr_t;
    virtual std::string getName(void) = 0;
    virtual void setSalary(float salary) = 0;
    virtual float getSalary(void) = 0;
    virtual std::string getRole(void) = 0;
};

class Developer : public Employee
{
  public:
    Developer(const std::string& name, float salary)
        : name_(name), salary_(salary), role_("Developer")
    {
    }

    std::string getName(void)
    {
      return name_;
    }

    void setSalary(float salary)
    {
      salary_ = salary;
    }

    float getSalary(void)
    {
      return salary_;
    }

    std::string getRole(void)
    {
      return role_;
    }

  private:
    std::string name_;
    float salary_;
    std::string role_;
};

class Designer : public Employee
{
  public:
    Designer(const std::string& name, float salary)
        : name_(name), salary_(salary), role_("Designer")
    {
    }

    std::string getName(void)
    {
      return name_;
    }

    void setSalary(float salary)
    {
      salary_ = salary;
    }

    float getSalary(void)
    {
      return salary_;
    }

    std::string getRole(void)
    {
      return role_;
    }

  private:
    std::string name_;
    float salary_;
    std::string role_;
};

class Organization
{
  public:
    void addEmployee(Employee::ptr_t employee)
    {
      employees_.push_back(employee);
    }

    float getNetSalaries(void)
    {
      float net = 0;
      for (auto employee : employees_) {
        net += employee->getSalary();
      }

      return net;
    }

  private:
    std::vector<Employee::ptr_t> employees_;
};

int main()
{
  // Prepare the employees.
  Employee::ptr_t jane = std::make_shared<Developer>("Jane Doe", 50000);
  Employee::ptr_t john = std::make_shared<Designer>("John Doe", 45000);

  // Add them to the organization.
  Organization org;
  org.addEmployee(jane);
  org.addEmployee(john);

  // Get the net salaries.
  std::cout << org.getNetSalaries() << std::endl; // Output: 95000

  return 0;
}
