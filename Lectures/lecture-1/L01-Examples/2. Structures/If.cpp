#include <iostream>

using namespace std;

/* If as specified by Pisula */
template <bool C, class ThenType, class ElseType>
struct If {
  typedef ThenType ret;
};

template <class ThenType, class ElseType>
struct If <false,ThenType,ElseType>{
  typedef ElseType ret;
};

//Using
struct Type1 {
  static inline void f() {
    cout<<"Pisula Statement 1"<<endl;
  }
};

struct Type2 {
  static inline void f() {
    cout<<"Pisula Statement 2"<<endl;
  }
};



/* If according to Todd Veldhuizen */
template <bool C>
class choice{};

template <>
class choice<true> {
  public:
		static inline void f() { cout<<"Veldhuizen Statement 1"<<endl; };
};

template <>
class choice<false> {
  public:
    static inline void f() { cout<<"Veldhuizen Statement 2"<<endl; };
};


int main(){

  If< (100 > 20), Type1, Type2 >::ret::f();  // static
  If< (100 < 20), Type1, Type2 >::ret::f();
    
    
  choice< (100 > 20) >::f();
  choice< (100 < 20) >::f();
 
	// OR 
	choice< (100 > 20) >* c = new choice< (100 > 20) >;
	c->f(); 
	delete c;
 // if (void f() { cout<<"Veldhuizen Statement 1"<<endl; };) // not static


  return 0;
}

/*
   Output
 
 Pisula Statement 1
 Pisula Statement 2
 Veldhuizen Statement 1
 Veldhuizen Statement 2
 Veldhuizen Statement 1
 
 */
