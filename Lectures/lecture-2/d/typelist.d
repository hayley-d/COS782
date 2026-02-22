import std.stdio;

// D does not have macros only templates
alias Typelist_1(T1) = Typelist!(T1, NullType);
alias Typelist_2(T1, T2) = Typelist!(T1, Typelist_1!T2);
alias Typelist_3(T1, T2, T3) = Typelist!(T1, Typelist_2!(T2, T3));
alias Typelist_4(T1, T2, T3, T4) = Typelist!(T1, Typelist_3!(T2, T3, T4));
alias Typelist_5(T1, T2, T3, T4, T5) = Typelist!(T1, Typelist_4!(T2, T3, T4, T5));
alias Typelist_6(T1, T2, T3, T4, T5, T6) = Typelist!(T1, Typelist_5!(T2, T3, T4, T5, T6));

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

template Erase(Tlist, T)
{
	static if (is(Tlist == NullType))
		alias Erase = NullType;
	else static if (is(Tlist.head == T))
		alias Erase = Tlist.tail;
	else
		alias Erase = Typelist!(Tlist.head, Erase!(Tlist.tail, T));
}

template EraseAll(Tlist, T)
{
	static if (is(Tlist == NullType))
		alias EraseAll = NullType;
	else static if (is(Tlist.head == T))
		alias EraseAll = EraseAll!(Tlist.tail, T);
	else
		alias EraseAll = Typelist!(Tlist.head, EraseAll!(Tlist.tail, T));
}

template NoDuplicates(Tlist)
{
	static if (is(Tlist == NullType))
		alias NoDuplicates = NullType;
	else
	{
		alias tempList = NoDuplicates!(Tlist.tail);
		alias tempListHead = Erase!(tempList, Tlist.head);
		alias NoDuplicates = Typelist!(Tlist.head, tempListHead);
	}
}

// Replace type T with type U
template Replace(Tlist, T, U)
{
	static if (is(Tlist == NullType))
		alias Replace = NullType;
	else static if (is(Tlist.head == T))
		alias Replace = Typelist!(U, Tlist.tail);
	else
		alias Replace = Typelist!(Tlist.head, Replace!(Tlist.tail, T, U));
}

template ReplaceAll(Tlist, T, U)
{
	static if (is(Tlist == NullType))
	{
		alias ReplaceAll = NullType;
	}
	else static if (is(Tlist.head == T))
	{
		alias temp = ReplaceAll!(Tlist.tail, T, U);
		alias ReplaceAll = Typelist!(U, temp);
	}
	else static if (is(Tlist.head.head))
	{
		alias temp = ReplaceAll!(Tlist.tail, T, U);
		alias temp2 = ReplaceAll!(Tlist.head, T, U);
		alias ReplaceAll = Typelist!(temp2, temp);
	}
	else
	{
		alias temp = ReplaceAll!(Tlist.tail, T, U);
		alias ReplaceAll = Typelist!(Tlist.head, temp);
	}
}

void main()
{
	alias allCharTypes = Typelist!(char, Typelist!(byte, Typelist!(ubyte, NullType)));
	alias SignedIntegrals = Typelist_4!(byte, short, int, long);
	writeln(
		"Length of allCharTypes: ", Length!allCharTypes);
	writeln(
		"Length of SignedIntegrals: ", Length!SignedIntegrals);
	static assert(
		is(TypeAt!(allCharTypes, 0) == char));
	static assert(
		is(TypeAt!(allCharTypes, 1) == byte));
	writeln("TypeAt!(allCharTypes, 0) is char: ", is(
			TypeAt!(allCharTypes, 0) == char));
	writeln("IndexOf char in allCharTypes: ", IndexOf!(
			allCharTypes, char));
	writeln("IndexOf ubyte in allCharTypes: ", IndexOf!(allCharTypes, ubyte));
	writeln("IndexOf int in allCharTypes: ", IndexOf!(allCharTypes, int));

	alias extended = Append!(allCharTypes, wchar);
	writeln("Length after append: ", Length!extended);

	alias remove = Erase!(allCharTypes, ubyte);
	writeln("Length after removing: ", Length!remove);

	alias intTypes = Typelist_4!(byte, int, int, long);
	alias removeAll = EraseAll!(intTypes, int);
	writeln("Length after removing all: ", Length!removeAll);
	alias intTypes2 = Typelist_4!(byte, int, int, Typelist_4!(
			long, int, int, long));
	alias removeDuplicates = NoDuplicates!(intTypes2);
	writeln("Length after removing duplicated: ", Length!removeDuplicates);

	alias replaceTypes = Typelist_6!(byte, int, int, long, int, int);
	alias replaceSingle = Replace!(replaceTypes, int, float);
	static assert(is(TypeAt!(replaceSingle, 1) == float));
	static assert(is(TypeAt!(replaceSingle, 2) == int));

	alias replaceAll = ReplaceAll!(replaceTypes, int, float);
	static assert(is(TypeAt!(replaceAll, 1) == float));
	static assert(is(TypeAt!(replaceAll, 2) == float));

	static assert(is(TypeAt!(replaceAll, 4) == float));
	static assert(is(TypeAt!(replaceAll, 5) == float));

}
