Input List: Typelist<int, Typelist<int, Typelist<long, NullType> > >

Step 1: NoDuplicates(Typelist<int, Typelist<int, Typelist<long, NullType> > >)
* Matches Typelist<Head, Tail>
* Head = Int;
* Tail = Typelist<int, Typelist<long, NullType> >;
* temp = NoDuplicates<Tail>;

Step 2: NoDuplicates(Typelist<int, Typelist<long, NullType> >)
* Matches Typelist<Head, Tail>
* Head = Int
* Tail = Typelist<long, NullType>;
* temp = NoDuplicates(Tail)

Step 3:  NoDuplicates(Typelist<long, NullType>)
* Matches Typelist<Head, Tail>
* Head = long
* Tail = NullType
* temp = NoDuplicates(NullType) => NullType
* temp2 = Erase(NullType, long) => Nulltype
* Result = Typelist<long, NullType>

Step 2 Backtrack: NoDuplicates(Typelist<int, Typelist<long, NullType> >)
* temp = Typelist<long, NullType>
* temp2 = Erase(Typelist<long, NullType>, Int) => Typelist<long, NullType>
* Result = Typelist<int, Typelist<long, NullType>>

Step 1 Backtrack: 
temp = Typelist<int, Typelist<long, NullType>>
temp2 = Erase<Typelist<int, Typelist<long, NullType>>, int> 
		→ Head (int) == T (int), so Result = Tail 
		= Typelist<long, NullType>
Result = Typelist<int, NoDuplicates<Typelist<long, NullType>>::Result> 
	   = Typelist<int, Typelist<long, NullType>> 
	   = [int, long]


