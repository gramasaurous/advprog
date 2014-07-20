// $Id: testxless.cpp,v 1.21 2014-04-24 17:42:23-07 - - $

// Example of how to use xless object on a pair of strings.

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <typename Type>
struct xless {
   bool operator() (const Type &left, const Type &right) const {
      return left < right;
   }
};

template <typename Type, class Less=xless<Type>>
void compare (const Type &left, const Type &right) {
   Less less;
   cout << boolalpha;
   bool is_less = less (left, right);
   bool is_equal = not less (left, right) and not less (right, left);
   bool is_greater = not is_less and not is_equal;
   cout << left << " <  " << right << " = " << is_less << endl;
   cout << left << " == " << right << " = " << is_equal << endl;
   cout << left << " >  " << right << " = " << is_greater << endl;
   cout << endl;
}

int main () {
   compare ("hello", "world");
   compare ("qwert", "qwert");
   compare ("zxcvb", "asdfg");
   return 0;
}

//TEST// testxless >testxless.out 2>&1
//TEST// mkpspdf testxless.ps testxless.cpp* testxless.out

