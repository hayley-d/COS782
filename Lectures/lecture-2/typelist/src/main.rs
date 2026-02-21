use typelist_macros::{define_typelist_system, typelist};

define_typelist_system!();

fn main() {
    type MyTypes = typelist!(i32, f64, char, bool);

    println!("Length: {}", MyTypes::LEN);

    let val: <MyTypes as TypeAt<1>>::Type = 3.14;
    println!("Value: {}", val);
}
