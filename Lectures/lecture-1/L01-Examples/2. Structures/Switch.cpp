#include <iostream>

using namespace std;

template <int I>
class Switch {
  public:
     static inline void f() { cout<<"Default Statement"<<endl; };
};

template <>
class Switch<1> {
  public:
     static inline void f() { cout<<"Statement 1"<<endl; };
};

template <>
class Switch<2> {
  public:
     static inline void f() { cout<<"Statement 2"<<endl; };
};


int main(){         // NOTE: Cannot use a for loop, need to call each with an actual value to enable it being static
  Switch<0>::f();
  Switch<1>::f();
  Switch<2>::f();
  Switch<3>::f();
  return 0; 
}

/*
   Output
 
 Default Statement
 Statement 1
 Statement 2
 Default Statement
 
 */
