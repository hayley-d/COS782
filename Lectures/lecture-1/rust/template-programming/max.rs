/* const fn max<T: PartialOrd>(a: T, b: T) -> &'static T {
    return if a > b { &a } else { &b };
}*/

macro_rules! max_macro {
    ($a:expr, $b:expr) => {
        if $a > $b {
            $a
        } else {
            $b
        }
    };
}

fn main() {
    println!("The largest between 10 and 2 is {}", max_macro!(10, 2));
    println!("The largest between a and b is {}", max_macro!('a', 'b'));
}
