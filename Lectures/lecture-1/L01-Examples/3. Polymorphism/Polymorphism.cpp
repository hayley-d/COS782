#include <iostream>

using namespace std;

// Static polymorphism - with structs (compile-time)
// Uses CRTP (Curiously recurring template pattern)
template <class SomeClass>
struct StructBase {
  void interface() {
    static_cast<SomeClass *>(this)->implementation();
  };
};

struct StructDerived : StructBase<StructDerived> {
  void implementation() {
    cout << "Static polymorphism - struct derived" << endl;
  };
};

struct StructDerived2 : StructBase<StructDerived2> {
  void implementation() {
    cout << "Static polymorphism - struct derived 2" << endl;
  };
};

/*
 * Compile-time polymorphism is not about making the execution at compile time
 rather making the dispatch decistion at compile-time so no v-table look up has
 to happen.

 * This is compile time evaluated since the function call is determined at
 * compile time. At compile time the compiler knows that p has the type
 * StructBase<StructDerived2>* and the cast will cast to StructDerived2* and
 * call the implementation method of that specific class.
 *
 * The compiler will generate the code that directly calls that function so that
 * no look up at runtime is needed.
 *
 * There is no v-table lookup when p->interface() is called.
 *
   p->interface();
   // Expands to:
   static_cast<StructDerived2*>(p)->implementation();
   // Which is a direct call to:
   StructDerived2::implementation();
 *
 */

// Static polymorphism - with classes

template <class SomeClass>
class ClassBase {
public:
  void interface() {
    static_cast<SomeClass *>(this)->implementation();
  };
};

class ClassDerived : public ClassBase<ClassDerived> {
public:
  void implementation() {
    cout << "Static polymorphism - class derived" << endl;
  };
};

class ClassDerived2 : public ClassBase<ClassDerived2> {
public:
  void implementation() {
    cout << "Static polymorphism - class derived 2" << endl;
  };
};

template <class SomeClass>
class Dog {
public:
  void speak() {
    static_cast<SomeClass *>(this)->speak();
  };
};

class Eevee : public Dog<Eevee> {
public:
  void speak() {
    cout << "I want biscuits\n";
  }
};

class Charlie : public Dog<Charlie> {
public:
  void speak() {
    cout << "I want to go on a walk\n";
  }
};

// Main program

int main() {
  StructBase<StructDerived2> *p = new StructDerived2; // Types must be the same
  p->interface();
  delete p;

  ClassBase<ClassDerived> *classp = new ClassDerived; // Type must be the same
  classp->interface();
  delete classp;

  Dog<Eevee> *eevee = new Eevee;
  Dog<Charlie> *charlie = new Charlie;
  return 0;
}

/*
   Output

 Dynamic polymorphism - Derived
 Static polymorphism - struct derived 2
 Static polymorphism - class derived

 */
