12/02/2026

Definition:
Generic Programming generalizes an algorithm with the help of templates so that it can be used with different data types.

In templates a placeholder is specified instead of the actual data type and the placeholder gets replaced with the data type during compilation.

If the template function is called for an integer, char and float the compiler will generate 3 copies of the function, one for each data type.

Example: Finding the max of two numbers

`template<typename T>`
`T max (T a, T b) {`
	`return (a > b ? a : b);`
`}`

`int main() {`
	`int x = 5, y= 7;`
	`float a = 7.7, b = 8.8;`

	 `// Prints 7` 
	 `std::cout << max(x, y) << std::endl;`

	 `// Prints 8.8`
	 `std::cout << max(a,b) << std::end;`
	 `return 0;`
`}`

