/*const fn factorial(num: u64) -> u64 {
    let mut result = num;
    let mut iter = num - 1;

    while iter > 0 {
        result *= iter;
        iter -= 1;
    }

    result
}*/

const fn factorial(num: u64) -> u64 {
    if num == 0 {
        return 1;
    }
    return num * factorial(num - 1);
}

fn main() {
    println!("The factorial of 4 is {}", factorial(4));
}
