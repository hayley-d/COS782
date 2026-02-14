#include <iostream>

using namespace std;

template<int n, template<int> class F>  // Note the use of the keyword class
struct Accumulate {
  enum {
    ret = Accumulate<n-1,F>::ret + F<n>::ret
  };
};

template<template<int> class F>
struct Accumulate<0,F> {
  enum {
    ret = F<0>::ret
  };
};

template <int n>
struct Square {
  enum {
    ret = n*n
  };
};

int main(){
  cout<< Accumulate<1,Square>::ret << endl;
  cout<< Accumulate<2,Square>::ret << endl;
  cout<< Accumulate<3,Square>::ret << endl;
  cout<< Accumulate<4,Square>::ret << endl;
  // cout<< Accumulate<-4,Square>::ret << endl;
    
  return 0;
}

/*
   Output
 
 1
 5
 14
 30
 
 */
