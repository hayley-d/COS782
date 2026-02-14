#include <iostream>

using namespace std;


template <int I>
class looptest {
	
  public:
	  static void f() {
		cout<<"Looping A "<<I<<endl;
		looptest < (I - 1) >::f();
		cout<<"Looping B "<<I<<endl;
	  };
};

template <>
class looptest<0> {
public:
	static inline void f(){ cout<<"------------"<<endl;};
	static void a() { cout << "============" << endl; };
};


template <int I>
class loop {
  private:
    enum { go = (I - 1) != 0 };
  public:
    static inline void f() {
	    cout<<"Looping A "<<I<<endl;
      loop < go ? (I - 1) : 0 >::f();
      cout<<"Looping B "<<I<<endl;
    };

	  static void a() {
			cout << "Hello " << I <<endl;
			loop < go ? (I - 1) : 0 >::a();
		};
 
};

template <>
class loop<0> {
  public:
	  static void a() { cout << "============" << endl; };
    static inline void f(){ cout<<"------------"<<endl;};

};



int main(){
	looptest<3>::f();
	
	loop<5>::f();
    loop<2>::a();
  return 0;
}

/*
   Output
 
 Looping A 3
 Looping A 2
 Looping A 1
 ------------
 Looping B 1
 Looping B 2
 Looping B 3
 Looping A 5
 Looping A 4
 Looping A 3
 Looping A 2
 Looping A 1
 ------------
 Looping B 1
 Looping B 2
 Looping B 3
 Looping B 4
 Looping B 5
 Hello 2
 Hello 1
 ============
 
 */
