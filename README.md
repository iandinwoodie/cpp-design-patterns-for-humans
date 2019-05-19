![C++ Design Patterns for Humans](https://user-images.githubusercontent.com/20260845/56855972-fb720600-691e-11e9-9efc-4755d6b4cb5b.png)

---

<p align="center">
🎉 Ultra-simplified explanation to design patterns! 🎉
</p>
<p align="center">
A topic that can easily make anyone's mind wobble. Here I try to make them stick
in to your mind (and maybe mine) by explaining them in the <i>simplest</i> way
possible. 
</p>
<p align="center">
This work is a derivative of
<a href="https://github.com/kamranahmedse/design-patterns-for-humans">
"Design Patterns for Humans"</a> by <a href="https://github.com/kamranahmedse">
kamranahmedse</a>, used under
<a href=https://creativecommons.org/licenses/by/4.0/">CC BY 4.0</a>.
</p>

---

## Introduction

Design patterns are solutions to recurring problems; **guidelines for how to
tackle certain problems**. They are not classes, packages, or libraries that
you can plug into your application and wait for the magic to happen. These are,
rather, guidelines on how to tackle certain problems in certain situations.

> Design patterns are solutions to recurring problems; guidelines for how to
tackle certain problems.

Wikipedia describes design patterns as:

> [...] a general reusable solution to a commonly occurring problem within a
given context in software design. It is not a finished design that can be
transformed directly into source or machine code. It is a description or
template for how to solve a problem that can be used in many different
situations.

### ⚠️ Be Careful

- Design patterns are not a silver bullet to all your problems.
- Do not try to force them; bad things are supposed to happen, if done so. 
- Keep in mind that design patterns are solutions **to** problems, not solutions 
**finding** problems; so don't overthink.
- If used in a correct place in a correct manner, they can prove to be a savior;
or else they can result in a horrible mess of a code.

## Types of Design Patterns

* [Creational](#creational-design-patterns)
* [Structural](#structural-design-patterns)
* [Behavioral](#behavioral-design-patterns)

## Creational Design Patterns

In plain words:

> Creational patterns are focused towards how to instantiate an object or group
of related objects.

Wikipedia says:

> In software engineering, creational design patterns are design patterns that
deal with object creation mechanisms, trying to create objects in a manner
suitable to the situation. The basic form of object creation could result in
design problems or added complexity to the design. Creational design patterns
solve this problem by somehow controlling this object creation.

 * [Simple Factory](#-simple-factory)
 * [Factory Method](#-factory-method)
 * [Abstract Factory](#-abstract-factory)
 * [Builder](#-builder)
 * [Prototype](#-prototype)
 * [Singleton](#-singleton)

### 🏠 Simple Factory

#### Overview

Real world example:

> Consider, you are building a house and you need doors. You can either put on
your carpenter clothes, bring some wood, glue, nails and all the tools required
to build the door and start building it in your house or you can simply call the
factory and get the built door delivered to you so that you don't need to learn
anything about the door making or to deal with the mess that comes with making
it.

In plain words:

> Simple factory simply generates an instance for client without exposing any
instantiation logic to the client.

Wikipedia says:

> In object-oriented programming (OOP), a factory is an object for creating
other objects – formally a factory is a function or method that returns objects
of a varying prototype or class from some method call, which is assumed to be
"new".

#### Programmatic Example

First of all we have a door base class and a wooden door derived class:

```cpp
class Door
{
  public:
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
```

Then we have our door factory that makes the door and returns it:

```cpp
class DoorFactory
{
  public:
    static std::shared_ptr<Door> makeDoor(float width, float height)
    {
      return std::make_shared<WoodenDoor>(width, height);
    }
};
```

Here is how this can be used:

```cpp
// Make a door with dimensions 100x200.
std::shared_ptr<Door> door = DoorFactory::makeDoor(100, 200);

std::cout << "width = " << door->getWidth() << std::endl;
// Output: width = 100
std::cout << "height = " << door->getHeight() << std::endl;
// Output: height = 200

// We can use the factory again to make a door with dimensions 50x100.
std::shared_ptr<Door> door2 = DoorFactory::makeDoor(50, 100);

std::cout << "width = " << door2->getWidth() << std::endl;
// Output: width = 50
std::cout << "height = " << door2->getHeight() << std::endl;
// Output: height = 100
```

#### When To Use

When creating an object is not just a few assignments and involves some logic, 
it makes sense to put it in a dedicated factory instead of repeating the same
code everywhere.

### 🏭 Factory Method

#### Overview

Real world example:

> Consider the case of a hiring manager. It is impossible for one person to 
interview for each of the positions. Based on the job opening, she has to decide
and delegate the interview steps to different people.

In plain words:

> It provides a way to delegate the instantiation logic to child classes.

Wikipedia says:

> In class-based programming, the factory method pattern is a creational pattern
that uses factory methods to deal with the problem of creating objects without
having to specify the exact class of the object that will be created. This is
done by creating objects by calling a factory method—either specified in an
interface and implemented by child classes, or implemented in a base class and
optionally overridden by derived classes—rather than by calling a constructor.

#### Programmatic Example

Taking our hiring manager example above. First of all we have an interviewer
interface and some implementations for it:

```cpp
class Interviewer
{
  public:
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
```

Now let us create our hiring manager class:

```cpp
class HiringManager
{
  public:
    void takeInterview(void)
    {
      std::shared_ptr<Interviewer> interviewer = makeInterviewer();
      interviewer->askQuestions();
    }

  protected:
    virtual std::shared_ptr<Interviewer> makeInterviewer(void) = 0;
};
```

Now any child can extend it and provide the required interviewer:

```cpp
class DevelopmentManager : public HiringManager
{
  protected:
    std::shared_ptr<Interviewer> makeInterviewer(void)
    {
      return std::make_shared<Developer>();
    }
};

class MarketingManager : public HiringManager
{
  protected:
    std::shared_ptr<Interviewer> makeInterviewer(void)
    {
      return std::make_shared<CommunityExecutive>();
    }
};
```

Here is how this can be used:

```cpp
DevelopmentManager developmentManager = DevelopmentManager();
developmentManager.takeInterview(); // Output: Asking about design patterns!

MarketingManager marketingManager = MarketingManager();
marketingManager.takeInterview(); // Output: Asking about community building!
```

#### When To Use

Useful when there is some generic processing in a class but the required
sub-class is dynamically decided at runtime. Or putting it in other words, when
the client doesn't know what exact sub-class it might need.

### 🔨 Abstract Factory

#### Overview

Real world example:

> Extending our door example from Simple Factory. Based on your needs you might
get a wooden door from a wooden door shop, iron door from an iron shop or a PVC
door from the relevant shop. Plus you might need a guy with different kind of
specialities to fit the door, for example a carpenter for wooden door, welder
for iron door etc. As you can see there is a dependency between the doors now,
wooden door needs carpenter, iron door needs a welder etc.

In plain words:

> A factory of factories; a factory that groups the individual but
related/dependent factories together without specifying their concrete classes.

Wikipedia says:

> The abstract factory pattern provides a way to encapsulate a group of
individual factories that have a common theme without specifying their concrete
classes.

#### Programmatic Example

Translating the door example above. First of all we have our door base class
and some derivation of it:

```cpp
class Door
{
  public:
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
```

Then we have some fitting experts for each door type:

```cpp
class DoorFittingExpert
{
  public:
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
```

Now we have our abstract factory that would let us make family of related
objects i.e. wooden door factory would create a wooden door and wooden door
fitting expert and iron door factory would create an iron door and iron door
fitting expert:

```cpp
class DoorFactory
{
  public:
    virtual std::shared_ptr<Door> makeDoor(void) = 0;
    virtual std::shared_ptr<DoorFittingExpert> makeFittingExpert(void) = 0;
};

class WoodenDoorFactory : public DoorFactory
{
  public:
    std::shared_ptr<Door> makeDoor(void)
    {
      return std::make_shared<WoodenDoor>();
    }

    std::shared_ptr<DoorFittingExpert> makeFittingExpert(void)
    {
      return std::make_shared<Carpenter>();
    }
};

class IronDoorFactory : public DoorFactory
{
  public:
    std::shared_ptr<Door> makeDoor(void)
    {
      return std::make_shared<IronDoor>();
    }

    std::shared_ptr<DoorFittingExpert> makeFittingExpert(void)
    {
      return std::make_shared<Welder>();
    }
};
```

Here is how this can be used:

```cpp
WoodenDoorFactory woodenFactory = WoodenDoorFactory();
std::shared_ptr<Door> door = woodenFactory.makeDoor();
std::shared_ptr<DoorFittingExpert> expert = woodenFactory.makeFittingExpert();

door->getDescription(); // Output: I am a wooden door.
expert->getDescription(); // Output: I can only fit wooden doors.

IronDoorFactory ironFactory = IronDoorFactory();
std::shared_ptr<Door> door2 = ironFactory.makeDoor();
std::shared_ptr<DoorFittingExpert> expert2 = woodenFactory.makeFittingExpert();

door2->getDescription(); // Output: I am an iron door.
expert2->getDescription(); // Output: I can only fit iron doors.
```

As you can see the wooden door factory has encapsulated the carpenter and the
wooden door also iron door factory has encapsulated the iron door and welder.
And thus it had helped us make sure that for each of the created door, we do not
get a wrong fitting expert.

#### When To Use

When there are interrelated dependencies with not-that-simple creation logic
involved.

### 👷 Builder

#### Overview

Real world example:

> Imagine you are at Hardee's and you order a specific deal, lets say,
"Big Hardee" and they hand it over to you without *any questions*; this is the
example of simple factory. But there are cases when the creation logic might
involve more steps. For example you want a customized Subway deal, you have
several options in how your burger is made e.g what bread do you want? what
types of sauces would you like? What cheese would you want? etc. In such cases
builder pattern comes to the rescue.

In plain words:

> Allows you to create different flavors of an object while avoiding constructor
pollution. Useful when there could be several flavors of an object. Or when
there are a lot of steps involved in creation of an object.

Wikipedia says:

> The builder pattern is an object creation software design pattern with the
intentions of finding a solution to the telescoping constructor anti-pattern.

Having said that let me add a bit about what telescoping constructor
anti-pattern is. At one point or the other we have all seen a constructor like
below:

```cpp
class Burger
{
  public:
    Burger(int patties, bool cheese = true, bool pepperoni = true,
           bool tomato = true, bool lettuce = true);
}
```

As you can see; the number of constructor parameters can quickly get out of hand
and it might become difficult to understand the arrangement of parameters. Plus
this parameter list could keep on growing if you would want to add more options
in future. This is called telescoping constructor anti-pattern.

#### Programmatic Example

The sane alternative is to use the builder pattern. First of all we have our
burger that we want to make:

```cpp
class Burger
{
  public:
    Burger(BurgerBuilder* builder);
        : patties_(builder->patties), cheese_(builder->cheese),
          pepperoni_(builder->pepperoni), lettuce_(builder->lettuce),
          tomato_(builder->tomato)
    {
    }

    void getDescription(void);
    {
      std::cout << patties_ << " patties";
      if (cheese_) {
        std::cout << ", cheese";
      }
      if (pepperoni_) {
        std::cout << ", pepperoni";
      }
      if (lettuce_){
        std::cout << ", lettuce";
      }
      if (tomato_) {
        std::cout << ", tomato";
      }
      std::cout << std::endl;
    }

  private:
    int patties_;
    bool cheese_;
    bool pepperoni_;
    bool lettuce_;
    bool tomato_;
};
```

And then we have the builder

```cpp
class BurgerBuilder
{
  public:
    BurgerBuilder(int patties)
        : patties(patties), cheese(false), pepperoni(false), lettuce(false),
          tomato(false)
    {
    }

    BurgerBuilder& addCheese(void)
    {
      cheese = true;
      return (*this);
    }

    BurgerBuilder& addPepperoni(void)
    {
      pepperoni = true;
      return (*this);
    }

    BurgerBuilder& addLettuce(void)
    {
      lettuce = true;
      return (*this);
    }

    BurgerBuilder& addTomato(void)
    {
      tomato = true;
      return (*this);
    }

    std::shared_ptr<Burger> build(void)
    {
      return std::make_shared<Burger>(this);
    }

    int patties;
    bool cheese;
    bool pepperoni;
    bool lettuce;
    bool tomato;
};

```

Here is how this can be used:

```cpp
// One double patty burger with no dairy.
std::shared_ptr<Burger> burger = BurgerBuilder(2).
    addPepperoni().
    addLettuce().
    addTomato().
    build();
burger->getDescription();
// Output: 2 patties, pepperoni, lettuce, tomato

// One triple patty buger with everything.
std::shared_ptr<Burger> burger2 = BurgerBuilder(3).
    addPepperoni().
    addCheese().
    addLettuce().
    addTomato().
    build();
burger2->getDescription();
// Output: 3 patties, cheese, pepperoni, lettuce, tomato
```

#### When To Use

When there could be several flavors of an object and to avoid the constructor
telescoping. The key difference from the factory pattern is that; factory
pattern is to be used when the creation is a one step process while builder
pattern is to be used when the creation is a multi step process.

### 🐑 Prototype

#### Overview

Real world example:

> Remember dolly? The sheep that was cloned! Lets not get into the details but
the key point here is that it is all about cloning.

In plain words:

> Create object based on an existing object through cloning.

Wikipedia says:

> The prototype pattern is a creational design pattern in software development.
It is used when the type of objects to create is determined by a prototypical
instance, which is cloned to produce new objects.

In short, it allows you to create a copy of an existing object and modify it to
your needs, instead of going through the trouble of creating an object from
scratch and setting it up.

#### Programmatic Example

Let's create a sheep class

```cpp
class Sheep
{
  public:
    Sheep(const std::string& name, const std::string& category)
        : name_(name), category_(category)
    {
    }

    void setName(const std::string name)
    {
      name_ = name;
    }

    std::string getName(void)
    {
      return name_;
    }

    void setCategory(const std::string category)
    {
      category_ = category;
    }

    std::string getCategory(void)
    {
      return category_;
    }

  private:
    std::string name_;
    std::string category_;
};
```
Here is how we can clone this object

```cpp
Sheep original = Sheep("Molly", "Mountain Sheep");
std::cout << original.getName() << std::endl; // Output: Molly
std::cout << original.getCategory() << std::endl; // Output: Mountain Sheep

Sheep clone = original;
clone.setName("Dolly");
std::cout << clone.getName() << std::endl; // Output: Dolly
std::cout << clone.getCategory() << std::endl; // Output: Mountain Sheep
```

#### When To Use

When an object is required that is similar to existing object or when the
creation would be expensive as compared to cloning.

### 💍 Singleton

#### Overview

Real world example:

> There can only be one president of a country at a time. The same president has
to be brought to action, whenever duty calls. President here is singleton.

In plain words:

> Ensures that only one object of a particular class is ever created.

Wikipedia says:

> In software engineering, the singleton pattern is a software design pattern
that restricts the instantiation of a class to one object. This is useful when
exactly one object is needed to coordinate actions across the system.

Singleton pattern is actually considered an anti-pattern and overuse of it
should be avoided. It is not necessarily bad and could have some valid use-cases
but should be used with caution because it introduces a global state in your
application and change to it in one place could affect in the other areas and it
could become pretty difficult to debug. The other bad thing about them is it
makes your code tightly coupled plus mocking the singleton could be difficult.

#### Programmatic Example

To create a singleton, make the constructor private, disable cloning, and create
a static variable to house the instance.

```cpp
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
```

Here is how this can be used:

```cpp
President& president1 = President::getInstance();
President& president2 = President::getInstance();

// There can only be 1 president, so they must be the same.
assert(&president1 == &president2);
```

#### When To Use

TODO

## Structural Design Patterns

In plain words:

> Structural patterns are mostly concerned with object composition or in other
words how the entities can use each other. Or yet another explanation would be,
they help in answering "How to build a software component?"

Wikipedia says:

> In software engineering, structural design patterns are design patterns that
ease the design by identifying a simple way to realize relationships between
entities.

 * [Adapter](#-adapter)
 * [Bridge](#-bridge)
 * [Composite](#-composite)
 * [Decorator](#-decorator)
 * [Facade](#-facade)
 * [Flyweight](#-flyweight)
 * [Proxy](#-proxy)

### 🔌 Adapter

#### Overview

Real world example:

> Consider that you have some pictures in your memory card and you need to
transfer them to your computer. In order to transfer them you need some kind of
adapter that is compatible with your computer ports so that you can attach
memory card to your computer. In this case card reader is an adapter.

Another real world example:

> Another example would be the famous power adapter; a three legged plug can't
be connected to a two pronged outlet, it needs to use a power adapter that makes
it compatible with the two pronged outlet.

And another:

> Yet another example would be a translator translating words spoken by one
person to another.

In plain words:

> Adapter pattern lets you wrap an otherwise incompatible object in an adapter
to make it compatible with another class.

Wikipedia says:

> In software engineering, the adapter pattern is a software design pattern that
allows the interface of an existing class to be used as another interface. It is
often used to make existing classes work with others without modifying their
source code.

#### Programmatic Example

Consider a game where there is a hunter and he hunts lions. First we have a
lion class that all types of lions have to implement.

```cpp
class Lion
{
  public:
    virtual void roar(void) = 0;
};

class AfricanLion : public Lion
{
  public:
    void roar(void)
    {
      std::cout << "*African lion roar*" << std::endl;
    }
};

class AsianLion : public Lion
{
  public:
    void roar(void)
    {
      std::cout << "*Asian lion roar*" << std::endl;
    }
};
```

And hunter expects any implementation of lion class.

```cpp
class Hunter
{
  public:
    void hunt(Lion& lion)
    {
      lion.roar();
    }
};
```
Now let's say we have to add a wild dog in our game so that hunter can hunt
that also (Note: I do not condone the hunting of any dogs). But we can't do that
directly because dog has a different interface. To make it compatible for our
hunter, we will have to create an adapter that is compatible.

```cpp
class WildDog
{
  public:
    void bark(void)
    {
      std::cout << "*wild dog bark*" << std::endl;
    }
};

class WildDogAdapter : public Lion
{
  public:
    WildDogAdapter(std::shared_ptr<WildDog> dog)
        : dog_(dog)
    {
    }

    void roar(void)
    {
      dog_->bark();
    }

  private:
    std::shared_ptr<WildDog> dog_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<WildDog> wildDog = std::make_shared<WildDog>();
WildDogAdapter wildDogAdapter(wildDog);

Hunter hunter;
hunter.hunt(wildDogAdapter); // Output: *wild dog bark*
```

#### When To Use

TODO

### 🚡 Bridge

#### Overview

Real world example:

> Consider you have a website with different pages and you are supposed to allow
the user to change the theme. What would you do? Create multiple copies of each
of the pages for each of the themes or would you just create separate theme and
load them based on the user's preferences? Bridge pattern allows you to do the
second i.e.

![With and without the bridge pattern](https://cloud.githubusercontent.com/assets/11269635/23065293/33b7aea0-f515-11e6-983f-98823c9845ee.png)

In plain words:

> Bridge pattern is about preferring composition over inheritance.
Implementation details are pushed from a hierarchy to another object with a
separate hierarchy.

Wikipedia says:

> The bridge pattern is a design pattern used in software engineering that is
meant to "decouple an abstraction from its implementation so that the two can
vary independently."

#### Programmatic Example

Translating our WebPage example from above. Here we have the web page hierarchy.

```cpp
class WebPage
{
  public:
    virtual std::string getContent(void) = 0;
};

class About : public WebPage
{
  public:
    About(std::shared_ptr<Theme> theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "About page in " + theme_->getColor();
    }

  private:
    std::shared_ptr<Theme> theme_;
};

class Projects : public WebPage
{
  public:
    Projects(std::shared_ptr<Theme> theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "Projects page in " + theme_->getColor();
    }

  private:
    std::shared_ptr<Theme> theme_;
};


class Careers : public WebPage
{
  public:
    Careers(std::shared_ptr<Theme> theme)
        : theme_(theme)
    {
    }

    std::string getContent(void)
    {
      return "Careers page in " + theme_->getColor();
    }

  private:
    std::shared_ptr<Theme> theme_;
};
```

And the separate theme hierarchy.

```cpp
class Theme
{
  public:
    virtual std::string getColor(void) = 0;
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
```

Here is how this can be used:

```cpp
std::shared_ptr<Theme> darkTheme = std::make_shared<DarkTheme>();
About about(darkTheme);
Careers careers(darkTheme);

std::cout << about.getContent() << std::endl;
// Output: About page in dark palette
std::cout << careers.getContent() << std::endl;
// Output: Careers page in dark palette
```

#### When To Use

TODO

### 🌿 Composite

#### Overview

Real world example:

> Every organization is composed of employees. Each of the employees has the
same features i.e. has a salary, has some responsibilities, may or may not
report to someone, may or may not have some subordinates etc.

In plain words:

> Composite pattern lets clients treat the individual objects in a uniform
manner.

Wikipedia says:

> In software engineering, the composite pattern is a partitioning design
pattern. The composite pattern describes that a group of objects is to be
treated in the same way as a single instance of an object. The intent of a
composite is to "compose" objects into tree structures to represent part-whole
hierarchies. Implementing the composite pattern lets clients treat individual
objects and compositions uniformly.

#### Programmatic Example

Taking our employees example from above. Here we have different employee types

```cpp
class Employee
{
  public:
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
```

Then we have an organization which consists of several different types of employees

```cpp
class Organization
{
  public:
    void addEmployee(std::shared_ptr<Employee> employee)
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
    std::vector<std::shared_ptr<Employee>> employees_;
};
```

Here is how this can be used:

```cpp
// Prepare the employees.
std::shared_ptr<Employee> jane = std::make_shared<Developer>("Jane", 50000);
std::shared_ptr<Employee> john = std::make_shared<Designer>("John", 45000);

// Add them to the organization.
Organization org;
org.addEmployee(jane);
org.addEmployee(john);

// Get the net salaries.
std::cout << org.getNetSalaries() << std::endl; // Output: 95000
```

#### When To Use

TODO

### ☕ Decorator

#### Overview

Real world example:

> Imagine you run a car service shop offering multiple services. Now how do you
calculate the bill to be charged? You pick one service and dynamically keep
adding to it the prices for the provided services till you get the final cost.
Here each type of service is a decorator.

In plain words:

> Decorator pattern lets you dynamically change the behavior of an object at
run time by wrapping them in an object of a decorator class.

Wikipedia says:

> In object-oriented programming, the decorator pattern is a design pattern that
allows behavior to be added to an individual object, either statically or
dynamically, without affecting the behavior of other objects from the same
class. The decorator pattern is often useful for adhering to the Single
Responsibility Principle, as it allows functionality to be divided between
classes with unique areas of concern.

#### Programmatic Example

Lets take coffee for example. First of all we have a simple coffee implementing
the coffee class

```cpp
class Coffee
{
  public:
    virtual float getPrice(void) = 0;
    virtual std::string getDescription(void) = 0;
};

class SimpleCoffee : public Coffee
{
  public:
    float getPrice(void)
    {
      return 3;
    }

    std::string getDescription(void)
    {
      return "Simple coffee";
    }
};
```

We want to make the code extensible to allow options to modify it if required.
Lets make some add-ons (decorators)

```cpp
class MilkCoffee : public Coffee
{
  public:
    MilkCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 0.5;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", milk";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

class WhipCoffee : public Coffee
{
  public:
    WhipCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 2;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", whip";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};

class VanillaCoffee : public Coffee
{
  public:
    VanillaCoffee(std::shared_ptr<Coffee> coffee)
        : coffee_(coffee)
    {
    }

    float getPrice(void)
    {
      return coffee_->getPrice() + 1;
    }

    std::string getDescription(void)
    {
      return coffee_->getDescription() + ", vanilla";
    }

  private:
    std::shared_ptr<Coffee> coffee_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Coffee> simple = std::make_shared<SimpleCoffee>();
std::cout << simple->getPrice() << std::endl;
// Output: 3
std::cout << simple->getDescription() << std::endl;
// Output: Simple coffee

std::shared_ptr<Coffee> milk = std::make_shared<MilkCoffee>(simple);
std::cout << milk->getPrice() << std::endl;
// Output: 3.5
std::cout << milk->getDescription() << std::endl;
// Output: Simple coffee, milk

std::shared_ptr<Coffee> whip = std::make_shared<WhipCoffee>(milk);
std::cout << whip->getPrice() << std::endl;
// Output: 5.5
std::cout << whip->getDescription() << std::endl;
// Output: Simple coffee, milk, whip

std::shared_ptr<Coffee> vanilla = std::make_shared<VanillaCoffee>(whip);
std::cout << vanilla->getPrice() << std::endl;
// Output: 6.5
std::cout << vanilla->getDescription() << std::endl;
// Output: Simple coffee, milk, whip, vanilla
```

#### When To Use

TODO

### 📦 Facade

#### Overview

Real world example:

> How do you turn on the computer? "Hit the power button" you say! That is what
you believe because you are using a simple interface that computer provides on
the outside, internally it has to do a lot of stuff to make it happen. This
simple interface to the complex subsystem is a facade.

In plain words:

> Facade pattern provides a simplified interface to a complex subsystem.

Wikipedia says:

> A facade is an object that provides a simplified interface to a larger body of
code, such as a class library.

#### Programmatic Example

Taking our computer example from above. Here we have the computer class

```cpp
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
```

Here we have the facade

```cpp
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
```

Here is how this can be used:

```cpp
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
```

#### When To Use

TODO

### 🍃 Flyweight

#### Overview

Real world example:

> Did you ever have fresh tea from some stall? They often make more than one
cup that you demanded and save the rest for any other customer so to save the
resources e.g. gas etc. Flyweight pattern is all about that i.e. sharing.

In plain words:

> It is used to minimize memory usage or computational expenses by sharing as
much as possible with similar objects.

Wikipedia says:

> In computer programming, flyweight is a software design pattern. A flyweight
is an object that minimizes memory use by sharing as much data as possible with
other similar objects; it is a way to use objects in large numbers when a simple
repeated representation would use an unacceptable amount of memory.

#### Programmatic Example

Translating our tea example from above. First of all we have tea types and tea
maker

```cpp
struct Tea
{
};

class TeaMaker
{
  public:
    std::shared_ptr<Tea> make(const std::string& preference)
    {
      auto match = availableTea_.find(preference);
      if (match == availableTea_.end()) {
        availableTea_[preference] = std::make_shared<Tea>();
      }

      return availableTea_[preference];
    }

    int getPreferenceCount(void)
    {
      return availableTea_.size();
    }

  private:
    std::unordered_map<std::string, std::shared_ptr<Tea>> availableTea_;
};
```

Then we have the tea shop which takes orders and serves them

```cpp
class TeaShop
{
  public:
    TeaShop(std::shared_ptr<TeaMaker> maker)
        : maker_(maker)
    {
    }

    void takeOrder(const std::string& preference, int table)
    {
      orders_[table] = maker_->make(preference);
    }

    void serve(void)
    {
      for (auto order : orders_) {
        std::cout << "Serving tea to table " << order.first << std::endl;
      }
    }

    int getPreferenceCount(void)
    {
      return maker_->getPreferenceCount();
    }

  private:
    std::shared_ptr<TeaMaker> maker_;
    std::unordered_map<int, std::shared_ptr<Tea>> orders_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<TeaMaker> maker = std::make_shared<TeaMaker>();
TeaShop shop(maker);

// No orders have been taken, so there are no available teas.
std::cout << shop.getPreferenceCount() << std::endl; // Output: 0

// Take some orders.
shop.takeOrder("half sugar", 1);
shop.takeOrder("with milk", 2);
shop.takeOrder("with boba", 5);

// We create a new batch of tea for each preference.
std::cout << shop.getPreferenceCount() << std::endl; // Output: 3

// Take an order with a previously requested preference.
shop.takeOrder("half sugar", 4);

// Since we have some tea from the last time this request was made, no new
// batch was created.
std::cout << shop.getPreferenceCount() << std::endl; // Output: 3

// Serve the customers.
shop.serve(); 
// Output: (Note: Since the map is unordered, the serving order may vary.)
// Serving tea to table 4
// Serving tea to table 5
// Serving tea to table 1
// Serving tea to table 2
```

#### When To Use

TODO

### 🎱 Proxy

#### Overview

Real world example:

> Have you ever used an access card to go through a door? There are multiple
options to open that door i.e. it can be opened either using access card or by
pressing a button that bypasses the security. The door's main functionality is
to open but there is a proxy added on top of it to add some functionality. Let
me better explain it using the code example below.

In plain words:

> Using the proxy pattern, a class represents the functionality of another
class.

Wikipedia says:

> A proxy, in its most general form, is a class functioning as an interface to
something else. A proxy is a wrapper or agent object that is being called by the
client to access the real serving object behind the scenes. Use of the proxy can
simply be forwarding to the real object, or can provide additional logic. In the
proxy extra functionality can be provided, for example caching when operations
on the real object are resource intensive, or checking preconditions before
operations on the real object are invoked.

#### Programmatic Example

Taking our security door example from above. Firstly we have the door class
and an implementation of door

```cpp
class Door
{
  public:
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
```

Then we have a proxy to secure any doors that we want

```cpp
class SecuredDoor
{
  public:
    SecuredDoor(std::shared_ptr<Door> door)
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

    std::shared_ptr<Door> door_;
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Door> labDoor = std::make_shared<LabDoor>();
SecuredDoor securedDoor(labDoor);

securedDoor.open("invalid"); // Output: No way, Jose!
securedDoor.open("Bond007"); // Output: Opening lab door
securedDoor.close(); // Output: Closing lab door
```

#### When To Use

TODO

## Behavioral Design Patterns

In plain words:

> It is concerned with assignment of responsibilities between the objects. What
makes them different from structural patterns is they don't just specify the
structure but also outline the patterns for message passing/communication
between them. Or in other words, they assist in answering "How to run a behavior
in software component?"

Wikipedia says:

> In software engineering, behavioral design patterns are design patterns that
identify common communication patterns between objects and realize these
patterns. By doing so, these patterns increase flexibility in carrying out this
communication.

* [Chain of Responsibility](#-chain-of-responsibility)
* [Command](#-command)
* [Iterator](#-iterator)
* [Mediator](#-mediator)
* [Memento](#-memento)
* [Observer](#-observer)
* [Visitor](#-visitor)
* [Strategy](#-strategy)
* [State](#-state)
* [Template Method](#-template-method)

### 🔗 Chain of Responsibility

#### Overview

Real world example:

> For example, you have three payment methods (`A`, `B` and `C`) setup in your
account; each having a different amount in it. `A` has 100 USD, `B` has 300 USD
and `C` having 1000 USD and the preference for payments is chosen as `A` then
`B` then `C`. You try to purchase something that is worth 210 USD. Using Chain
of Responsibility, first of all account `A` will be checked if it can make the
purchase, if yes purchase will be made and the chain will be broken. If not,
request will move forward to account `B` checking for amount if yes chain will
be broken otherwise the request will keep forwarding till it finds the suitable
handler. Here `A`, `B` and `C` are links of the chain and the whole phenomenon
is Chain of Responsibility.

In plain words:

> It helps building a chain of objects. Request enters from one end and keeps
going from object to object till it finds the suitable handler.

Wikipedia says:

> In object-oriented design, the chain-of-responsibility pattern is a design
pattern consisting of a source of command objects and a series of processing
objects. Each processing object contains logic that defines the types of command
objects that it can handle; the rest are passed to the next processing object in
the chain.

#### Programmatic Example

Translating our account example above. First of all we have a base account
having the logic for chaining the accounts together and some accounts.

```cpp
class Account
{
  public:
    Account(void)
        : name_("empty account"), balance_(0), successor_()
    {
    }

    void setNext(std::shared_ptr<Account> account)
    {
      successor_ = account;
    }

    void pay(float amount)
    {
      if (canPay(amount)) {
        std::cout << "Paid " << amount << " using " << name_ << "."
                  << std::endl;
        balance_ -= amount;
      } else if (successor_) {
        std::cout << "Cannot pay using " << name_ << ". Proceeding ..."
                  << std::endl;
        successor_->pay(amount);
      } else {
        std::cerr << "None of the accounts have enough balance." << std::endl;
      }
    }

    bool canPay(float amount)
    {
      return balance_ >= amount;
    }

  protected:
    std::string name_;
    float balance_;
    std::shared_ptr<Account> successor_;
};

class Bank : public Account
{
  public:
    Bank(float balance)
    {
      name_ = "bank";
      balance_ = balance;
    }
};

class Paypal : public Account
{
  public:
    Paypal(float balance)
    {
      name_ = "paypal";
      balance_ = balance;
    }
};

class Bitcoin : public Account
{
  public:
    Bitcoin(float balance)
    {
      name_ = "bitcoin";
      balance_ = balance;
    }
};
```

Now let's prepare the chain using the links defined above (i.e., Bank, Paypal,
Bitcoin).

```cpp
// We are going to create the chain: bank->paypal->bitcoin.

// First, create the accounts.
std::shared_ptr<Bank> bank = std::make_shared<Bank>(100);
std::shared_ptr<Paypal> paypal = std::make_shared<Paypal>(200);
std::shared_ptr<Bitcoin> bitcoin = std::make_shared<Bitcoin>(300);

// Next, establish the order.
bank->setNext(paypal);
paypal->setNext(bitcoin);

// Let's try to pay using the first priority (i.e., the bank).
bank->pay(250);
// Output:
// Cannot pay using bank. Proceeding ...
// Cannot pay using paypal. Proceeding ...
// Paid 250 using bitcoin.
```

#### When To Use

TODO

### 👮 Command

#### Overview

Real world example:

> A generic example would be you ordering food at a restaurant. You (i.e.
`Client`) ask the waiter (i.e. `Invoker`) to bring some food (i.e. `Command`)
and waiter simply forwards the request to Chef (i.e. `Receiver`) who has the
knowledge of what and how to cook.

Another example:

> Another example would be you (i.e. `Client`) switching on (i.e. `Command`) the
television (i.e. `Receiver`) using a remote control (`Invoker`).

In plain words:

> Allows you to encapsulate actions in objects. The key idea behind this pattern
is to provide the means to decouple client from receiver.

Wikipedia says:

> In object-oriented programming, the command pattern is a behavioral design
pattern in which an object is used to encapsulate all information needed to
perform an action or trigger an event at a later time. This information includes
the method name, the object that owns the method and values for the method
parameters.

#### Programmatic Example

First of all we have the receiver that has the implementation of every action
that could be performed.

```cpp
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
```

Then we have an interface that each of the commands are going to implement and
then we have a set of commands.

```cpp
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
```

Then we have an invoker with whom the client will interact to process any
commands.

```cpp
// The invoker.
class RemoteControl
{
  public:
    void submit(std::shared_ptr<Command> command)
    {
      command->execute();
    }
};
```

Here is how this can be used:

```cpp
std::shared_ptr<Bulb> bulb = std::make_shared<Bulb>();

std::shared_ptr<TurnOn> turnOn = std::make_shared<TurnOn>(bulb);
std::shared_ptr<TurnOff> turnOff = std::make_shared<TurnOff>(bulb);

RemoteControl remote;
remote.submit(turnOn);
remote.submit(turnOff);
// Output:
// Bulb has been lit.
// Darkness!
```

Command pattern can also be used to implement a transaction based system. Where
you keep maintaining the history of commands as soon as you execute them. If the
final command is successfully executed, all good otherwise just iterate through
the history and keep executing the `undo` on all the executed commands.

#### When To Use

TODO

### ➿ Iterator

#### Overview

Real world example:

> An old radio set will be a good example of iterator, where user could start at
some channel and then use next or previous buttons to go through the respective
channels. Or take an example of MP3 player or a TV set where you could press the
next and previous buttons to go through the consecutive channels or in other
words they all provide an interface to iterate through the respective channels,
songs or radio stations.

In plain words:

> It presents a way to access the elements of an object without exposing the
underlying presentation.

Wikipedia says:

> In object-oriented programming, the iterator pattern is a design pattern in
which an iterator is used to traverse a container and access the container's
elements. The iterator pattern decouples algorithms from containers; in some
cases, algorithms are necessarily container-specific and thus cannot be
decoupled.

#### Programmatic Example

TODO

#### When To Use

TODO

### 👽 Mediator

#### Overview

Real world example:

> A general example would be when you talk to someone on your mobile phone,
there is a network provider sitting between you and them and your conversation
goes through it instead of being directly sent. In this case network provider is
mediator.

In plain words:

> Mediator pattern adds a third party object (called mediator) to control the
interaction between two objects (called colleagues). It helps reduce the
coupling between the classes communicating with each other. Because now they
don't need to have the knowledge of each other's implementation.

Wikipedia says:

> In software engineering, the mediator pattern defines an object that
encapsulates how a set of objects interact. This pattern is considered to be a
behavioral pattern due to the way it can alter the program's running behavior.

#### Programmatic Example

TODO

#### When To Use

TODO

### 💾 Memento

#### Overview

Real world example:

> Take the example of calculator (i.e. originator), where whenever you perform
some calculation the last calculation is saved in memory (i.e. memento) so that
you can get back to it and maybe get it restored using some action buttons (i.e.
caretaker).

In plain words:

> Memento pattern is about capturing and storing the current state of an object
in a manner that it can be restored later on in a smooth manner.

Wikipedia says:

> The memento pattern is a software design pattern that provides the ability to
restore an object to its previous state (undo via rollback).

Usually useful when you need to provide some sort of undo functionality.

#### Programmatic Example

TODO

#### When To Use

TODO

### 😎 Observer

#### Overview

Real world example:

> A good example would be the job seekers where they subscribe to some job
posting site and they are notified whenever there is a matching job opportunity.

In plain words:

> Defines a dependency between objects so that whenever an object changes its
state, all its dependents are notified.

Wikipedia says:

> The observer pattern is a software design pattern in which an object, called
the subject, maintains a list of its dependents, called observers, and notifies
them automatically of any state changes, usually by calling one of their
methods.

#### Programmatic Example

TODO

#### When To Use

TODO

### 🏃 Visitor

#### Overview

Real world example:

> Consider someone visiting Dubai. They just need a way (i.e. visa) to enter
Dubai. After arrival, they can come and visit any place in Dubai on their own
without having to ask for permission or to do some leg work in order to visit
any place here; just let them know of a place and they can visit it. Visitor
pattern lets you do just that, it helps you add places to visit so that they can
visit as much as they can without having to do any legwork.

In plain words:

> Visitor pattern lets you add further operations to objects without having to
modify them.

Wikipedia says:

> In object-oriented programming and software engineering, the visitor design
pattern is a way of separating an algorithm from an object structure on which it
operates. A practical result of this separation is the ability to add new
operations to existing object structures without modifying those structures. It
is one way to follow the open/closed principle.

#### Programmatic Example

TODO

#### When To Use

TODO

### 💡 Strategy

#### Overview

Real world example:

> Consider the example of sorting, we implemented bubble sort but the data
started to grow and bubble sort started getting very slow. In order to tackle
this we implemented Quick sort. But now although the quick sort algorithm was
doing better for large datasets, it was very slow for smaller datasets. In order
to handle this we implemented a strategy where for small datasets, bubble sort
will be used and for larger, quick sort.

In plain words:

> Strategy pattern allows you to switch the algorithm or strategy based upon the
situation.

Wikipedia says:

> In computer programming, the strategy pattern (also known as the policy
pattern) is a behavioural software design pattern that enables an algorithm's
behavior to be selected at runtime.

#### Programmatic Example

TODO

#### When To Use

TODO

### 💢 State

#### Overview

Real world example:

> Imagine you are using some drawing application, you choose the paint brush to
draw. Now the brush changes its behavior based on the selected color i.e. if you
have chosen red color it will draw in red, if blue then it will be in blue etc.

In plain words:

> It lets you change the behavior of a class when the state changes.

Wikipedia says:

> The state pattern is a behavioral software design pattern that implements a
state machine in an object-oriented way. With the state pattern, a state machine
is implemented by implementing each individual state as a derived class of the
state pattern interface, and implementing state transitions by invoking methods
defined by the pattern's superclass. The state pattern can be interpreted as a
strategy pattern which is able to switch the current strategy through 
invocations of methods defined in the pattern's interface.

#### Programmatic Example

TODO

#### When To Use

TODO

### 📒 Template Method

#### Overview

Real world example:

> Suppose we are getting some house built. The steps for building might look
like:
> - Prepare the base of house
> - Build the walls
> - Add roof
> - Add other floors
>
> The order of these steps could never be changed i.e. you can't build the roof
before building the walls etc but each of the steps could be modified for
example walls can be made of wood or polyester or stone.

In plain words:

> Template method defines the skeleton of how a certain algorithm could be
performed, but defers the implementation of those steps to the children classes.

Wikipedia says:

> In software engineering, the template method pattern is a behavioral design
pattern that defines the program skeleton of an algorithm in an operation,
deferring some steps to subclasses. It lets one redefine certain steps of an
algorithm without changing the algorithm's structure.

#### Programmatic Example

TODO

#### When To Use

TODO

## 🚦 Wrap Up

And that about wraps it up. I will continue to improve this, so you might want
to watch/star this repository to revisit. Also, I have plans on writing the same
about the architectural patterns, stay tuned for it.

## 👬 Contribution

- Report issues
- Open pull request with improvements
- Spread the word

## License

All content of this file, unless otherwise noted, is licensed as follows:

- All provided source code examples are covered by the
[MIT License](https://github.com/idinwoodie/cpp-design-patterns-for-humans/blob/master/LICENSE).
- The C++ badge that appears in the banner image was created by
[Jeremy Kratz](https://jeremykratz.com/) and is licensed by
[The Standard C++ Foundation](https://isocpp.org/home/terms-of-use).
- Other content, including images, is released under the
[Creative Common Attribution 4.0 International License](https://creativecommons.org/licenses/by/4.0/).
