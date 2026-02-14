#include <iostream>

using namespace std;

// Dynamic polymorphism

class Base {
  public:
    virtual void interface() { cout<<"Dynamic polymorphism - Base"<<endl; };
};

class Derived : public Base {
  public:
    virtual void interface() { cout<<"Dynamic polymorphism - Derived"<<endl; };
};


// Static polymorphism - with structs

template <class SomeClass>
struct StructBase {
  void interface(){
   static_cast<SomeClass*>(this)->implementation();
  };
};

struct StructDerived : StructBase<StructDerived> {
  void implementation() { cout<<"Static polymorphism - struct derived"<<endl; };
};

struct StructDerived2 : StructBase<StructDerived2> {
  void implementation() { cout<<"Static polymorphism - struct derived 2"<<endl; };
};

// Static polymorphism - with classes

template <class SomeClass>
class ClassBase {
  public:
   void interface(){
    static_cast<SomeClass*>(this)->implementation();
   };
};

class ClassDerived : public ClassBase<ClassDerived> {
  public:
    void implementation() { cout<<"Static polymorphism - class derived"<<endl; };
};

class ClassDerived2 : public ClassBase<ClassDerived2> {
  public:
    void implementation() { cout<<"Static polymorphism - class derived 2"<<endl; };
};

// Main program

int main(){
  Base *pBase = new Derived;
  pBase->interface();
  delete pBase;
	
  StructBase<StructDerived2> *p = new StructDerived2;  // Types must be the same
  p->interface();
  delete p;

  ClassBase<ClassDerived> *classp = new ClassDerived;  // Type must be the same
  classp->interface();
  delete classp;

  return 0;
}

/*
   Output
 
 Dynamic polymorphism - Derived
 Static polymorphism - struct derived 2
 Static polymorphism - class derived
 
 */
