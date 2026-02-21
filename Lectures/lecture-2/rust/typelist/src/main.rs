#![feature(generic_const_exprs)]
#![feature(specialization)]

use typelist_macros::typelist;

struct NullType {}

struct Typelist<Head, Tail> {
    head: Head,
    tail: Tail,
}

trait Length {
    const LEN: usize;
}

impl Length for NullType {
    const LEN: usize = 0;
}

impl<Head, Tail: Length> Length for Typelist<Head, Tail> {
    const LEN: usize = 1 + Tail::LEN;
}

// Rust is not capable of generics using specialization with const expression such as a const usize
struct Zero;
struct Successor<N>(std::marker::PhantomData<N>);

trait TypeAt<N> {
    type Type;
}

impl<Head, Tail> TypeAt<Zero> for Typelist<Head, Tail> {
    type Type = Head;
}

impl<Head, Tail, N> TypeAt<Successor<N>> for Typelist<Head, Tail>
where
    Tail: TypeAt<N>,
{
    type Type = <Tail as TypeAt<N>>::Type;
}

struct NotFound;

trait IndexOf<T> {
    type Index;
}

impl<T, Tail> IndexOf<T> for Typelist<T, Tail> {
    type Index = Zero;
}

impl<Head, Tail, T> IndexOf<T> for Typelist<Head, Tail>
where
    Tail: IndexOf<T>,
{
    type Index = Successor<<Tail as IndexOf<T>>::Index>::Index;
}

impl<T> IndexOf<T> for NullType {
    type Index = NotFound;
}

fn main() {
    type MyTypes = typelist!(i32, f64, char);

    const X: MyTypes = Typelist {
        head: 42i32,
        tail: Typelist {
            head: 3.14f64,
            tail: Typelist {
                head: 'a',
                tail: NullType {},
            },
        },
    };

    const LENGTH: usize = MyTypes::LEN;

    type First = <MyTypes as TypeAt<Zero>>::Type;
    type Second = <MyTypes as TypeAt<Successor<Zero>>>::Type;
    type Third = <MyTypes as TypeAt<Successor<Successor<Zero>>>>::Type;

    println!("Worked");
    println!("The length of the typelist is {}", LENGTH);
}
