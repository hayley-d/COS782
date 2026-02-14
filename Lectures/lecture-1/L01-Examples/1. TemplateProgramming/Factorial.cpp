#include <assert.h>
#include <iostream>

int factorialRecursive(int);

// The use of a ternary operator here instead of using a base case the compiler
// tries to interpret both branches of the ternary. So when MetaFactorial2<1> is
// called the compiler tries to evaluate 1 == 1 ? 1 : 1 *
// MetaFactorial<1-1>::Value and then it will try to evaluate MetaFactorial<1-1>
// and so on to check both branches are valid. This eventually its an infinite
// loop of evaluation as it goes into negative numbers.
/* template <int a>
struct MetaFactorial2 {
  // Enum is used to force the value to be computed at compile time and store it
  // as a literal
  // A static const int occupies memory where as an enum is a symbolic constant
  enum { value = a == 1 ? 1 : a * MetaFactorial2<a - 1>::value };
}; */

// You could solve the issue by defining a base case at 0 or 1 but that defiets
// the point of the ternary.
/*
template <>
struct MetaFactorial2<1> {
  enum { value = 1 };
};
*/

// This instance uses template specialization which prevents the compiler from
// going into an infinite loop of evaluation as it will hit 0 and only evaluate
// value = 1 not more potential recursive calls.
template <int n>
class MetaFactorial {
public:
  enum { value = n * MetaFactorial<n - 1>::value };
};

template <>
class MetaFactorial<0> {
public:
  enum { value = 1 };
};

int main() {
  std::cout << "Recursive " << factorialRecursive(5) << std::endl;
  std::cout << "Meta " << MetaFactorial<5>::value << std::endl;
  return 0;
}

int factorialRecursive(int n) {
  assert(0 <= n);
  if (0 == n)
    return 1;
  return n * factorialRecursive(n - 1);
}

/*
 Output:
 Recursive 120
 Meta 120
*/

// In Rust as a const function
/*
 * const fn factorial(n: u64) -> u64 {
 *   if n == 0 { return 1; }
 *   return n * factorial(n-1);
 * }
 */
