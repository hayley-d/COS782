#include <iostream>

using namespace std;

template <int From, int To>
class loop;

template <int From, int To, bool Less>
class loopChoice;

template <int From, int To, bool Stop>
class loopAsc;

template <int From, int To, bool Stop>
class loopDesc;




template <int From, int To>
class loop {
private:
	enum { go = (From <= To) };
public:
	static void l() {
		loopChoice <From, To, go>::l();
	};
};


template <int From, int To>
class loopChoice <From, To, true> {
	public: 
	  static void l() {
			cout << "Ascending" << endl;
			loopAsc <From, To, true>::l();
		}
};


template <int From, int To, bool Stop>
class loopAsc {
  private:
	  enum { stop = (From < To) };
  public: 
	  static void l() {
			cout << "Count " << From << " " << To << endl;
			loopAsc <From + 1, To, stop>::l();
		}
};

template <int From, int To>
class loopAsc<From, To, false> {
public: 
	static void l() {
		cout << "------" << endl;
	}
};


template <int From, int To>
class loopChoice <From, To, false> {
public: 
	static void l() {
		cout << "Descending" << endl;
		loopDesc <From, To, true>::l();
	}
};

template <int From, int To, bool Stop>
class loopDesc {
private:
	enum { stop = (From > To) };
public: 
	static void l() {
		cout << "Count " << From << " " << To << endl;
		loopDesc <From - 1, To, stop>::l();
	}
};

template <int From, int To>
class loopDesc<From, To, false> {
public: 
	static void l() {
		cout << "------" << endl;
	}
};

int main(){
	loop<5,3>::l();
    loop<2,5>::l();
	loop<2,2>::l();
	loop<2,1>::l();
  return 0;
}


/*
   Output
 
 Descending
 Count 5 3
 Count 4 3
 Count 3 3
 ------
 Ascending
 Count 2 5
 Count 3 5
 Count 4 5
 Count 5 5
 ------
 Ascending
 Count 2 2
 ------
 Descending
 Count 2 1
 Count 1 1
 ------
 
 */
