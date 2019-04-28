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

TODO

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

TODO

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

TODO

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

TODO

As you can see; the number of constructor parameters can quickly get out of hand
and it might become difficult to understand the arrangement of parameters. Plus
this parameter list could keep on growing if you would want to add more options
in future. This is called telescoping constructor anti-pattern.

#### Programmatic Example

TODO

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

TODO

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

TODO

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

TODO

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

TODO

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

TODO

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

TODO

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

TODO

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

TODO

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

TODO

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

#### Programmatic Example

TODO

#### When To Use

### 👮 Command

#### Overview

#### Programmatic Example

TODO

#### When To Use

### ➿ Iterator

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 👽 Mediator

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 💾 Memento

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 😎 Observer

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 🏃 Visitor

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 💡 Strategy

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 💢 State

#### Overview

#### Programmatic Example

TODO

#### When To Use

### 📒 Template Method

#### Overview

#### Programmatic Example

TODO

#### When To Use


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
