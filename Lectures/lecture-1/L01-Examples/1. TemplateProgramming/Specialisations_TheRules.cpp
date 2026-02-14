/*
   Template specialisations
   ========================
*/

// General

		template<typename U, typename T>
		class Foo {};
		

// Partial

		template<typename T>
		class Foo<string, T> {};
		

// Total

		template<>
		class Foo<string, string> {};
		



// Templates with templates
// ========================

		template<typename V>
		class Foo<string, vector<V> > {};
		
		
// Template member functions cannot be specialised, only overloaded

		template<typename U, typename T>
		T Fun(U obj);
		
		template<typename T>
		T Fun(string obj);
		
		// Return type cannot be specialised.