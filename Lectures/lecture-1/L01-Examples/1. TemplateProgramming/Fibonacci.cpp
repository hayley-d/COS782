#include <iostream>

template <int n>
constexpr int fib() {
  return fib<n - 1>() + fib<n - 2>();
}

template <>
constexpr int fib<2>() {
  return 1;
}

template <>
constexpr int fib<1>() {
  return 1;
}

int main() {
  std::cout << fib<3>() << "\n";
}
