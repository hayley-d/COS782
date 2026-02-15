#include <string>
#include <vector>

/*
   Template specialisations
   Specialization is when you provide specific implementation for certain
   template parameters

   when the compiler goes to choose which funciton definition is used for the
   call it will pick the most specific match. So if there is a total
   specialization that matches that one is used, if there is only a partial
   specialization that matches that one is used otherwise the general
   specialization is used.

   Specialisation can only be used for classes. You overload if you use a
   function.

   With specialisation you have a general template and when you declare a
   partial/total specialisation it says that this class is based off the
   original so the signature must be the same but if the type of the class is
   defined then use that template instead.

   template<typename T>
   class Container {
                void store(T value);
   };

   // See template is empty meaning this is based off the existing template, if
   you remove the general template this will cause an error saying the template
   is not defined.

   template<>
   class Container<bool> {
                void store(bool value);
   }

   With overloading they are independent of eachother, if I remove one it does
   not have an effect on the other. They are two seporate templates. You can
   change the return type and parameter list as long as you don't try

   template<typename T>
   T foo(T obj) { } // Allowed

   template<typename T>
   T foo(string object) { } // Allowed

   // This issue with this one is it's attempting to specialise when functions
   cannot be specialised

   template<typename T>
   T foo<T>(bool obj) { } // Not allowed the foo<T> is the issue here, as that
   is attempting to specialise


*/

// General

template <typename U, typename T>
class Foo {};

// Partial

template <typename T>
class Foo<std::string, T> {};

// Total

template <>
class Foo<std::string, std::string> {};

// Templates with templates
// ========================

template <typename V>
class Foo<std::string, std::vector<V>> {};

// Template member functions cannot be specialised, only overloaded

template <typename U, typename T>
T Fun(U obj);

template <typename T>
T Fun(std::string obj);

// Return type cannot be specialised.
