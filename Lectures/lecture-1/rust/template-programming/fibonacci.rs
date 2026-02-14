// How you would handle it when coding normally
fn fibonacci_run_time(num: u64) -> u64 {
    match num {
        0 => 0,
        1 => 1,
        _ => fibonacci_run_time(num - 1) + fibonacci_run_time(num - 2),
    }
}

// Compile time generated const function
const fn fibonacci(nth_term: u64) -> u64 {
    match nth_term {
        0 => 0,
        1 => 1,
        _ => fibonacci(nth_term - 1) + fibonacci(nth_term - 2),
    }
}

fn main() {
    println!("Fibonacci at compile time {}", fibonacci(10));
}
