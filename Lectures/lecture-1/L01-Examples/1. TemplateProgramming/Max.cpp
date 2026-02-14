#include <iostream>

// Defines a macro that takes in a and b and returns the larger number unless
// otherwise specified
// The issue with using macros is that you cannot ensure that the values being
// passed in implement the comparison
#define MaxMacro(a, b) ((a) > (b) ? (a) : (b))

// The reason this is evaluated at run-time not compile time is because its just
// a templatized function not an enum. So the function call will happen at
// run-time. It has nothing to do with it using references
template <typename T>
T &max(T &a, T &b) {
  return a > b ? a : b;
}

template <int a, int b>
struct MaxInt {
  enum { val = a > b ? a : b };
};

template <int a, int b>
class MaxIntClass_Enum {
public:
  enum { val = a > b ? a : b };
};

// No longer valid in more modern compilers - compiles, but throws a linker
// error
// This is due to the fact that its a ternary value and it won't be able to
// assign a value to the memeory location for val
/*
template<int a, int b>
class MaxIntClass_Static {
  public:
    static int const val = a > b ? a :b;
};
*/

template <int a, int b>
class MaxIntClassFunc {
public:
  static int func() {
    return a > b ? a : b;
  };
};

void foo(int const &);

int main() {
  int a = 20;
  int b = 30;

  double c = 24.5;
  double d = 7.7;

  char e = 'a';
  char f = 'b';

  std::cout << "Macro" << std::endl;
  std::cout << MaxMacro(20, 30) << std::endl;     // Compile-time
  std::cout << MaxMacro(22.4, 22.8) << std::endl; // compile-time
  std::cout << MaxMacro('a', 'b') << std::endl;   // compile-time

  std::cout << "Template function" << std::endl;
  std::cout << max(a, b) << std::endl;         // run-time *
  std::cout << max<double>(c, d) << std::endl; // run-time
  std::cout << max<char>(e, f) << std::endl;   // run-time

  std::cout << "Struct" << std::endl;
  std::cout << MaxInt<20, 10>::val << std::endl; // compile-time

  MaxInt<34, 22> x;
  std::cout << x.val << std::endl; // compile-time
  MaxInt<66, 106> *y = new MaxInt<66, 106>;
  std::cout << y->val << std::endl; // run-time
  delete y;

  std::cout << "Class - constant" << std::endl;
  std::cout << MaxIntClass_Enum<200, 100>::val << std::endl; // compile-time

  std::cout << "  Motivation for using enum" << std::endl;
  foo(MaxIntClass_Enum<200, 100>::val); // only in compile time

  std::cout << "Class - function" << std::endl;
  std::cout << MaxIntClassFunc<250, 111>::func() << std::endl; // run time
}

void foo(int const &value) {
  std::cout << "value = " << value << std::endl;
}

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
