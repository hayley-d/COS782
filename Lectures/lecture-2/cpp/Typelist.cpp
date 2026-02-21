#include <iostream>

// Some macros to define typelists to prevent repetition.
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>

// Typelist struct - A simple typelist structure
// Typelist holds two types a ead and tail
template <typename Head, typename Tail>
struct Typelist {
  typedef Head head;
  typedef Tail tail;
};

// An nullable type for the end of the typelist
struct NullType {};

// Calculating the length
// Uses partial template specialization to distinguish between the null type and
// a type list.
template <typename TList>
struct Length;

// Base case (total specialization)
template <>
struct Length<NullType> {
  enum { value = 0 };
};

// Generic Case (partial specialization)
// Says head counts as one then get the length of the tail so like in functional
// programming it processes the head and then passes the rest of the list into
// the recursive function.
template <typename Head, typename Tail>
struct Length<Typelist<Head, Tail>> {
  enum { value = 1 + Length<Tail>::value };
};

int main() {
  typedef Typelist<int, NullType> onlyOneType;
  typedef Typelist<char,
                   Typelist<signed char, Typelist<unsigned char, NullType>>>
      allCharTypes;

  typedef TYPELIST_4(signed char, short int, int, long int) SignedIntegrals;

  const int length_of_type_list = Length<allCharTypes>::value;
  std::cout << "The length of all char types type is " << length_of_type_list
            << std::endl;

  return 0;
}

// TypeAt Implementation
template <typename Tlist, unsigned int>
struct TypeAt;

template <typename Head, typename Tail>
struct TypeAt<Typelist<Head, Tail>, 0> {
  typedef Head Result;
};

template <typename Head, typename Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i> {
  typedef typename TypeAt<Tail, i - 1>::Result Result;
};
