#include <iostream>
using namespace std;

#define MaxMacro(a, b) ((a) > (b) ? (a) : (b))

template <typename T> T &max(T &a, T &b) { return a > b ? a : b; }

template <int a, int b> struct MaxInt {
  enum { val = a > b ? a : b };
};

template <int a, int b> class MaxIntClass_Enum {
public:
  enum { val = a > b ? a : b };
};

// No longer valid in more modern compilers - compiles, but throws a linker
// error

/*
template<int a, int b>
class MaxIntClass_Static {
  public:
    static int const val = a > b ? a :b;
};
*/

template <int a, int b> class MaxIntClassFunc {
public:
  static int func() { return a > b ? a : b; };
};

void foo(int const &);

int main() {
  int a = 20;
  int b = 30;

  cout << "Macro" << endl;
  cout << MaxMacro(20, 30) << endl;
  cout << MaxMacro(22.4, 22.8) << endl;
  cout << MaxMacro('a', 'b') << endl;

  cout << "Template function" << endl;
  cout << max(a, b) << endl;
  cout << max<double>(24.8, 13.5) << endl;
  cout << max('a', 'b') << endl;

  cout << "Struct" << endl;
  cout << MaxInt<20, 10>::val << endl;

  MaxInt<34, 22> x;
  cout << x.val << endl;
  MaxInt<66, 106> *y = new MaxInt<66, 106>;
  cout << y->val << endl;
  delete y;

  cout << "Class - constant" << endl;
  cout << MaxIntClass_Enum<200, 100>::val << endl;
  //  cout << MaxIntClass_Static<200, 100>::val << endl;

  cout << "  Motivation for using enum" << endl;
  foo(MaxIntClass_Enum<200, 100>::val); // only in compile time
  //  foo(MaxIntClass_Static<200, 100>::val); // lvalue, implies static memory
  //  used. Run-time manipulation required.  enums are not lvalues

  cout << "Class - function" << endl;
  cout << MaxIntClassFunc<250, 111>::func() << endl;
}

void foo(int const &value) { cout << "value = " << value << endl; }

/*
   Output

 Macro
 30
 22.8
 b
 Template function
 30
 24.8
 b
 Struct
 20
 34
 106
 Class - constant
 200
 Motivation for using enum
 value = 200
 Class - function
 250

 */
