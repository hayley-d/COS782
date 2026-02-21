template square(T)
{
	T square(T t)
	{
		return t * t;
	}
}

import std.stdio;

void main()
{
	writeln("Noop Noop");
	writeln("Result of 4 suqared: ", square(4));
}
