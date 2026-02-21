#include <iostream>
#include <tuple>

// the typedef keyword is used to create an alias
// A typelist is a way to manipulate types at compile time;
// Typelists store a list of types.

// An ancillary type that marks the end of a typelist.
struct NullType {};

template <typename Head, typename Tail>
struct Typelist {
  typedef Head head;
  typedef Tail tail;
};

// C++11 introduced variadic templates, which make typelists much cleaner:
// // Modern typelist
template <typename... Types>
struct TypelistVariadic {};

template <typename T>
struct Length;

template <size_t I, typename T>
struct TypeAt;

template <typename... Types>
struct Length<TypelistVariadic<Types...>> {
  static constexpr size_t value = sizeof...(Types);
};

template <typename... Types, size_t I>
struct TypeAt<I, TypelistVariadic<Types...>> {
  using result = std::tuple_element_t<I, std::tuple<Types...>>;
};

int main() {
  // A version of the typelist that holds all floating points is
  typedef Typelist<float, Typelist<double, Typelist<long double, NullType>>>
      floating_point_types;

  typedef TypelistVariadic<int, double, char> MyTypes; // Variadic typelist
                                                       //
  std::cout << "Length: " << Length<MyTypes>::value << std::endl;
  TypeAt<1, MyTypes>::result myVar = 3.14;

  std::cout << "Value: " << myVar << std::endl;
  return 0;
};

/*
 * - A typelist can participate as one of the types in a larger typelist.
 * - A typelist can appear in another typelist only in the tail position, not in
 * the head;
 *
 * As you can see by the floating point typelist it can become very verbose with
 * all the <> brackets. A better solution is to use templates for generating
 * typelists.
 *
 */
