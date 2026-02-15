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
  constexpr int result = fib<3>();
  std::cout << result << "\n";
}
