macro_rules! max {
    ($a: expr, $b:expr) => {
        if $a > $b {
            $a
        } else {
            $b
        }
    };
}

fn main() {
    println!("Max value of 7 and 10 is {}", max!(7, 10));
    println!("Max value of a and z is {}", max!('a', 'z'));
}
