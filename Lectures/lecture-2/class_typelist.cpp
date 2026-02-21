#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>

struct NullType {};

template <class Head, class Tail>
struct Typelist {
  typedef Head head;
  typedef Tail tail;
};

// Type At
template <class TList, unsigned int index>
struct TypeAt;

template <class Head, class Tail>
struct TypeAt<Typelist<Head, Tail>, 0> {
  typedef Head Result;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i> {
  typedef typename TypeAt<Tail, i - 1>::Result Result;
};

// Index of

template <class TList, class T>
struct IndexOf;

template <class T>
struct IndexOf<NullType, T> {
  enum { value = -1 };
};

template <class T, class Tail>
struct IndexOf<Typelist<T, Tail>, T> {
  enum { value = 0 };
};

template <class Head, class Tail, class T>
struct IndexOf<Typelist<Head, Tail>, T> {
private:
public:
  enum { temp = IndexOf<Tail, T>::value };
  enum { value = temp == -1 ? -1 : 1 + temp };
};

template <class TList, class T>
struct Append;

template <>
struct Append<NullType, NullType> {
  typedef NullType Result;
};

template <class T>
struct Append<NullType, T> {
  typedef TYPELIST_1(T) Result;
};

template <class Head, class Tail>
struct Append<NullType, Typelist<Head, Tail>> {
  typedef Typelist<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>,
              T> typedef Typelist<Head, typename Append<Tail, T>::Result>
    Result;
}
;
