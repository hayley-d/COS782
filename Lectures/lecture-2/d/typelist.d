import std.stdio;

// D does not have macros only templates
alias Typelist_1(T1) = Typelist!(T1, NullType);
alias Typelist_2(T1, T2) = Typelist!(T1, Typelist_1!T2);
alias Typelist_3(T1, T2, T3) = Typelist!(T1, Typelist_2!(T2, T3));
alias Typelist_4(T1, T2, T3, T4) = Typelist!(T1, Typelist_3!(T2, T3, T4));

struct NullType
{
}

struct Typelist(H, T)
{
	alias head = H;
	alias tail = T;
}

template Length(Tlist)
{
	static if (is(Tlist == NullType))
		enum Length = 0;
	else
		enum Length = 1 + Length!(Tlist.tail);
}

template TypeAt(Tlist, uint i)
{
	static if (i == 0)
		alias TypeAt = Tlist.head;
	else
		alias TypeAt = TypeAt!(Tlist.tail, i - 1);
}

template IndexOf(Tlist, T)
{
	static if (is(Tlist == NullType))
		enum IndexOf = -1;
	else static if (is(Tlist.head == T))
		enum IndexOf = 0;
	else
	{
		enum temp = IndexOf!(Tlist.tail, T);
		enum IndexOf = temp == -1 ? -1 : 1 + temp;
	}
}

template Append(Tlist, T)
{
	static if (is(Tlist == NullType) && is(T == NullType))
		alias Append = NullType;
	else static if (is(Tlist == NullType))
		alias Append = Typelist!(T, NullType);
	else
		alias Append = Typelist!(Tlist.head, Append!(Tlist.tail, T));
}

void main()
{
	alias allCharTypes = Typelist!(char, Typelist!(byte, Typelist!(ubyte, NullType)));
	alias SignedIntegrals = Typelist_4!(byte, short, int, long);

	writeln("Length of allCharTypes: ", Length!allCharTypes);
	writeln("Length of SignedIntegrals: ", Length!SignedIntegrals); 

	static assert(is(TypeAt!(allCharTypes, 0) == char));
	static assert(is(TypeAt!(allCharTypes, 1) == byte));
	writeln("TypeAt!(allCharTypes, 0) is char: ", is(TypeAt!(allCharTypes, 0) == char));

	writeln("IndexOf char in allCharTypes: ", IndexOf!(allCharTypes, char)); 
	writeln("IndexOf ubyte in allCharTypes: ", IndexOf!(allCharTypes, ubyte)); 
	writeln("IndexOf int in allCharTypes: ", IndexOf!(allCharTypes, int)); 

	alias extended = Append!(allCharTypes, wchar);
	writeln("Length after append: ", Length!extended); 
}
