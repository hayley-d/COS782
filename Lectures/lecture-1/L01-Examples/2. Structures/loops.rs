
const fn loop(num: u64) -> u64{
    let mut total = num;
    let mut iter = 0;
    while iter != num {
        total += 1;
        iter += 1;
    }

    total
}

fn main() {
    // Make sure its in a const context
    // Compile-time
    const RESULT: u64 = loop(3);
    println!("This loops 3 times {}", RESULT);

    // Compile time
    static RESULT_STATIC: u64 = loop(3);
    println!("This loops 3 times {}", RESULT);

    // Compile-time
    // Array sizes must be const computed at compile time so this would be impossible if not
    // evaluated at compile time
    let arr: [i32, loop(3)];


    // This makes it run-time
    println!("This loops 3 times {}", loop(3)); 
    // run-time
    let x = loop(3);
}
