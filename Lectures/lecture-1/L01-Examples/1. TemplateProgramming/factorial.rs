const fn factorial(num: u64) -> u64 {
    let mut result = num;
    let mut iter = num - 1;

    while iter > 0 {
        result *= iter;
        iter -= 1;
    }

    result
}

macro_rules! factorial_macro {
    // Entry
    ($num: expr) => {
        factorial_macro($num, $num - 1)
    };

    ($num: expr, 0) => {
        0
    };

    ($num: expr, 1) => {
        $num
    };

    ($num: expr, $iter: expr) => {
        fuctorial_macro($num * $iter, $iter - 1);
    };
}

fn main() {
    println!("The factorial of 4 is {}", factorial(4));
}
