trait Animal {
    const fn speak(&self);
}

struct Dog;
struct Cat;

impl Animal for Dog {
    const fn speak(&self) {
        println!("Woof");
    }
}

impl Animal for Cat {
    const fn speak(&self) {
        println!("Meow");
    }
}

const fn make_speak<T: Animal>(animal: &T) {
    animal.speak();
}

fn main() {
    const dog = Dog;
    dog.speak();
}
