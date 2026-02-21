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

// Index of Implementation
template <typename Tlist, typename T>
struct IndexOf;

template <typename T>
struct IndexOf<NullType, T> {
  enum { value = -1 };
};

template <typename Head, typename Tail, typename T>
struct IndexOf<Typelist<Head, Tail>, T> {
private:
  enum { temp = IndexOf<Tail, T>::value };

public:
  enum { value = temp == -1 ? -1 : 1 + temp };
};

// Append to a typelist
// Since it is not possbile to modify an existing typelist this will return a
// new typelist that contains the result
template <typename Tlist, typename T>
struct Append {};

// If the Typelist is null & type T is null
template <>
struct Append<NullType, NullType> {
  typedef NullType Result;
};

// If  The typelist is null and T is a single non-null type
template <typename T>
struct Append<NullType, T> {
  typedef TYPELIST_1(T) Result;
};

// if the typelist is null and T is a typelist
template <typename Head, typename Tail>
struct Append<NullType, Typelist<Head, Tail>> {
  typedef Typelist<Head, Tail> Result;
};

// else Typelist is non-null
// The result of having TList head as the head and appending T to the
// TList::Tail
template <typename Head, typename Tail, typename T>
struct Append<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
};

// Same as before you cannot modify a typelist so return a new typelist
template <typename Tlist, typename T>
struct Erase {};

// Empty typelist
template <typename T>
struct Erase<NullType, T> {
  typedef NullType Result;
};

// T is the same as the head then return the tail
template <typename Head, typename Tail>
struct Erase<Typelist<Head, Tail>, Head> {
  typedef Tail Result;
};

// else
template <typename Head, typename Tail, typename T>
struct Erase<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename Erase<Tail, T>::Result> Result;
};

// Erase all
template <typename Tlist, typename T>
struct EraseAll {};

// Empty typelist
template <typename T>
struct EraseAll<NullType, T> {
  typedef NullType Result;
};

// If head == T
template <typename Head, typename Tail>
struct EraseAll<Typelist<Head, Tail>, Head> {
  typedef typename EraseAll<Tail, Head>::Result Result;
};

// else
template <typename Head, typename Tail, typename T>
struct EraseAll<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename EraseAll<Tail, T>::Result> Result;
};

template <typename Tlist>
struct NoDuplicates {};

// empty list
template <>
struct NoDuplicates<NullType> {
  typedef NullType Result;
};

// else
template <typename Head, typename Tail>
struct NoDuplicates<Typelist<Head, Tail>> {
private:
  typedef typename NoDuplicates<Tail>::Result temp;
  typedef typename Erase<temp, Head>::Result temp2;

public:
  typedef Typelist<Head, typename NoDuplicates<temp2>::Result> Result;
};

// [byte, int, int, long]
