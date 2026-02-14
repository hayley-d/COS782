#include <assert.h>
#include <iostream>

int factorialIterative(int n);
int factorialRecursive(int);

template <int a> struct MetaFactorial2 {
  // Enum is used to force the value to be computed at compile time and store it
  // as a literal
  // A static const int occupies memory where as an enum is a symbolic constant
  enum { value = a == 1 ? 1 : a * MetaFactorial2<a - 1>::value };
};

template <int n> class MetaFactorial {
public:
  enum { value = n * MetaFactorial<n - 1>::value };
};

template <> class MetaFactorial<0> {
public:
  enum { value = 1 };
};

int main() {
  std::cout << "Recursive " << factorialRecursive(5) << std::endl;
  std::cout << "Meta " << MetaFactorial<5>::value << std::endl;
  std::cout << "Meta 2" << MetaFactorial2<5>::value << std::endl;

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
