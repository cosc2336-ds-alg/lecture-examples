/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   February 2, 2019
 * @assg   Inheritance and Composition
 *
 * @description Using Inheritance and Composition in
 *   C++ for OOAD (Object-oriented analysis and design)
 */
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/** Animal class definition
 * Our abstract base class, the base of a hierarchy of animal types.
 *
 * @var name A name of our animal friend.
 * @var typeName A const, the class/type name, used to display info
 *   about this animal object.
 * @var age The age as an int of this animal.
 */
class Animal
{
private:
  string name;
  string typeName = "Animal";
  int age;
  string attributes;

public:
  Animal(string name, int age);
  void addAttribute(string newAttributes);
  void setTypeName(string newTypeName);
  virtual string tostring() const;
  friend ostream& operator<<(ostream& out, const Animal& animal);
};

/** Animal constructor
 * Constructor for the Animal class.  Set the name and age parameters.
 * Will be invoked by derived classes.
 */
Animal::Animal(string name, int age)
{
  this->name = name;
  this->age = age;
  this->attributes = "alive";
}

/** set attributes
 * Set the attributes for this Animal type.  This is an example of
 * a method that is intended to be overrideen by derived classes.
 * Derived classes should override, call their base class to set
 * more basic attributes, then add their own attributes to the Animal.
 *
 * newAttributes A string of new attributes to append to our list
 *   of animal attributes.
 */
void Animal::addAttribute(string newAttributes)
{
  attributes += ", " + newAttributes;
}

/** set typeName
 * Set our animal type name.  Each derived class should override this
 * method and set an appropriate type name for display purposes.
 *
 * @param newTypeName The name to set for our animal typeName
 */
void Animal::setTypeName(string newTypeName)
{
  this->typeName = newTypeName;
}

/** represent Animal as string
 * Convert our current state to a string.  Can be overridden by
 * base clases, so can insert their own information about
 * the animal.
 *
 * NOTE: needs to be virtual to work as we want it to.
 *
 * @returns string Returns a string representation of this
 *   Animal.
 */
string Animal::tostring() const
{
  ostringstream out;

  out << "Hello I am " << name << " the " << typeName << ".  I am " << age << " years old" << endl;

  out << "  I have the following attributes: (" << attributes << ")";

  return out.str();
}

/** Animal stream insertion
 * Output representation of an animal to the given output stream.
 * This friend functin simply invokes tostring() on the Animal
 * object given.  If tostring() is virtual, it will do the right
 * thing and call most specific tostring() function.
 *
 * @param out The output stream we are to insert our Animal out to.
 * @param animal The object of type Animal we are displaying out
 *   to the stream.
 *
 * @returns ostream Returns the output stream that was passed in,
 *   but after we have inserted extra information about the animal
 *   into it.
 */
ostream& operator<<(ostream& out, const Animal& animal)
{
  // we use tostring() method, canbe overridden
  // by sub classes if needed.
  out << animal.tostring();
  return out;
}

/** Bird class definition
 * A Bird "isa" Animal.  This is just a simple example of
 * defining a derived class using inheritance.
 *
 */
class Bird : public Animal
{
private:
public:
  Bird(string name, int age);
};

/*** Bird constructor
 * The constructor for the Bird class.
 */
Bird::Bird(string name, int age)
  : Animal(name, age)
{
  // Some attributes specific to Birds
  addAttribute("has feathers");
  addAttribute("has wings");
  addAttribute("flys");
  addAttribute("lays eggs");

  // Our actualy more specific type name, for display
  setTypeName("Bird");
}

/** Mammal class definition
 * A Mammal "isa" Animal.  This is just a simple example of
 * defining a derived class using inheritance.
 *
 */
class Mammal : public Animal
{
private:
public:
  Mammal(string name, int age);
};

/** Mammal constructor
 * The constructor for the Mammal class
 */
Mammal::Mammal(string name, int age)
  : Animal(name, age)
{
  // some attributes specific to Mammals
  addAttribute("has fur");
  addAttribute("live birth");
  addAttribute("warm blooded");

  // Our actual more specific type name, for display
  setTypeName("Mammal");
}

/** Banana class definition
 * A banana class, food for our monkeys.
 */
class Banana
{
private:
  string color;
  bool eaten;

public:
  Banana(string color, bool eaten);
  void eat();
  void setColor(string color);
  friend ostream& operator<<(ostream& out, const Banana& banana);
};

/** Banana constructor
 * A banana class to feed the monkey.  Example of using
 * composition for "has-a" relationships.
 */
Banana::Banana(string color, bool eaten = false)
{
  this->color = color;
  this->eaten = eaten;
}

/** eat the banana
 */
void Banana::eat()
{
  this->eaten = true;
}

/** banana color setter
 * Set the banana color
 *
 * @param color the new color for the banana.
 */
void Banana::setColor(string color)
{
  this->color = color;
}

/** Banana stream insertion
 * Display the banana contents on the given output stream.
 */
ostream& operator<<(ostream& out, const Banana& banana)
{
  if (banana.eaten)
  {
    out << "This " << banana.color << " banana was eaten and it was yummy!";
  }
  else
  {
    out << "I haven't eaten the " << banana.color << " banana yet.";
  }

  return out;
}

/** Monkey class definition
 * A Monkey "isa" Mammal "isa" Animal.  This is just an example of
 * defining a derived class using inheritance.  In this case we
 * actually add some new private attributes to our derived Monkey.
 *
 * @var numberOfBananas The number of bananas I have to eat.
 */
class Monkey : public Mammal
{
private:
  int numberOfBananas;
  Banana* myBananas[10];

public:
  Monkey(string name, int age);
  string tostring() const;
  void giveBanana(Banana& aBanana);
  void eatBanana(int bananaNum);
};

/** Monkey constructor
 * Constructor for the Monkey class.  Notice we can chain call our
 * base class constructor still, while initializing new paramters
 * in this constructor.
 */
Monkey::Monkey(string name, int age)
  : Mammal(name, age)
{
  addAttribute("climbs trees");
  addAttribute("likes bananas");
  setTypeName("Monkey");
  this->numberOfBananas = 0;
}

/** represent Monkey as string
 * Convert our current state to a string.  Monkeys have
 * bananas, so we add that to the output.
 *
 * @returns string Returns a string representation of this
 *   Monkey
 */
string Monkey::tostring() const
{
  ostringstream out;

  // we init with string from base class
  out << Mammal::tostring() << endl;

  // and we append on our own information
  out << "  I have " << numberOfBananas << " bananas.  Yum!";
  for (int index = 0; index < numberOfBananas; index++)
  {
    out << endl;
    out << "  " << *myBananas[index];
  }

  return out.str();
}

/** give banana to monkey
 * Give a monkey a banana.
 *
 * @param aBanana A reference to an instance of a Banana object to
 *   give them.  Once we give the monkey a banana, then the monkey
 *   "has-a" banana.
 */
void Monkey::giveBanana(Banana& aBanana)
{
  myBananas[numberOfBananas] = &aBanana;
  numberOfBananas++;
}

/** Cat class definition
 * A Cat "isa" Mammal "isa" Animal.  This is just an example of
 * defining a derived class using inheritance.  In this case we
 * actually add some new private attributes to our derived Cat
 *
 * @var myHooman The person whos presence I tolerate for food and
 *   skritches.
 * @var numberOfLives Cats have 9 lives, unless otherwise stated
 */
class Cat : public Mammal
{
private:
  string myHooman;
  int numberOfLives;

public:
  Cat(string name, int age, string myHooman, int numberOfLives);
  string tostring() const;
};

/** Cat constructor
 * Constructor for the Cat class.  Notice we can chain call our
 * base class constructor still, while initializing new paramters
 * in this constructor.
 *
 * @param name My name
 * @param age My age in years
 * @param myHooman The person who lives with me in my house
 * @param numberOfLives The lives I have left to live, defaults to 9 for
 *   cats unless otherwise specified.
 */
Cat::Cat(string name, int age, string myHooman, int numberOfLives = 9)
  : Mammal(name, age)
{
  addAttribute("likes fish");
  addAttribute("loves to nap");
  this->myHooman = myHooman;
  this->numberOfLives = numberOfLives;
  setTypeName("Cat");
}

/** represent Cat as string
 * Convert our current state to a string.  Cats have
 * many lives and live with hoomans
 *
 * @returns string Returns a string representation of this
 *   Cat
 */
string Cat::tostring() const
{
  ostringstream out;

  // we init with string from base class
  out << Mammal::tostring() << endl;

  // append on the cat specific information
  out << "  I have " << numberOfLives << " lives" << endl;
  out << "  I live with my hooman " << myHooman << " they are nice, I have trained them to feed me fish";

  return out.str();
}

/** main
 * The main entry point for this program.  Execution of this program
 * will begin with this main function.
 *
 * @param argc The command line argument count which is the number of
 *     command line arguments provided by user when they started
 *     the program.
 * @param argv The command line arguments, an array of character
 *     arrays.
 *
 * @returns An int value indicating program exit status.  Usually 0
 *     is returned to indicate normal exit and a non-zero value
 *     is returned to indicate an error condition.
 */
int main(int argc, char** argv)
{
  // Examples of object Inheritance (is-a)
  Animal myAnimal("Abstract", 5);
  cout << myAnimal << endl << endl;

  Bird robbieTheBird("Robbie", 8);
  cout << robbieTheBird << endl << endl;

  Mammal dougTheMammal("Doug", 4);
  cout << dougTheMammal << endl << endl;

  Monkey georgeTheMonkey("George", 5);
  cout << georgeTheMonkey << endl << endl;

  Cat peteTheCat("Pete", 3, "Susan"); // use defualt param for # of lives
  cout << peteTheCat << endl << endl;

  // Examples of object composition (aggregation or has-a)
  Banana aBanana("green");
  cout << aBanana << endl;
  aBanana.eat();
  cout << aBanana << endl << endl;

  georgeTheMonkey.giveBanana(aBanana);
  Banana anotherBanana("yellow");
  georgeTheMonkey.giveBanana(anotherBanana);
  cout << georgeTheMonkey << endl << endl;

  // return 0 to indicate successful completion from main function
  // and our program
  return 0;
}
