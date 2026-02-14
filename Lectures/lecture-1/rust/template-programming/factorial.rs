// Normal factorial function
fn factorial_normal(n: u32) -> u32 {
    if n == 0 {
        1
    } else {
        n * factorial_normal(n - 1)
    }
}

// Constant evaluation is the process of computing the result of expressions during compilation.
// Const function is a function that can be called from a const context.
// When called from a const context a const function is interpreted by the compiler at compile
// time.
// When a const function is called outside a const context is behaves as if it did not have the
// const qualifier.
// The body of a const funciton may only use const expressions.

/* This is not allowed since you cannot use recursion with const funcitons
const fn factorial(n: u32) -> u32 {
    if n == 0 {
        1
    } else {
        n * factorial(n-1);
    }
} */

// You can use a normal while loop
const fn factorial(n: u32) -> u32 {
    let mut result = 1;
    let mut iter = n;
    while iter > 0 {
        result *= iter;
        iter -= 1;
    }
    result
}

fn main() {
    const RESULT: u32 = factorial(5);
    println!("Compile Time Factorial {}", RESULT);
}
