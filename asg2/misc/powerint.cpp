// $Id: powerint.cpp,v 1.13 2014-04-09 17:39:43-07 - - $

//
// NAME
//    powerint - power function raising a double to an int power
//
// SYNOPSIS
//    double powi (double base, int exponent);
//
// DESCRIPTION
//    The powi() function computes the value of base raised to the
//    power exponent.
//
// RETURN VALUES
//    Upon successful completion, powi() returns the value of base
//    raised to the power of exponent.  If exponent is 0, 1.0 is
//    returned regardless of the value of base (a number, 0, NaN,
//    or +-Infinity).  Otherwise multiplication and division are
//    subject to the rules of IEEE-754 floating point arithmetic,
//    for CPUs which support that.
//
// MATHEMATICS USED
//
//    powi (x, - n)   => powi (1 / x, n)
//    powi (x, 2 n)   => powi (x ** 2, n / 2)
//    powi (x, n + 1) => x * powi (x, n)
//
//    .EQ
//    x sup { - n }   = { ( 1 / x ) ) } sup n
//    x sup { 2 n }   = ( x sup 2 ) sup { n / 2 }
//    x sup { n + 1 } = x ( x sup n )
//    .EN
//
//    $$
//    x ^ { - n}    = { ( 1 / x ) } ^ n
//    x ^ { 2 n }   = ( x ^ 2 ) ^ ( n / 2 )
//    x ^ { n + 1 } = x ( x ^ n )
//    $$
//
//

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <libgen.h>
#include <limits>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

const int DIGITS = numeric_limits<double>::digits10 + 6;

template <typename item_t>
item_t from_string (const string &arg) {
   stringstream stream {arg};
   item_t result;
   stream >> result;
   return result;
}

void print_powi (double base, int exponent, double result) {
   cout << "powi: " << base << " ** " << exponent << " * "
        << result << endl;
}

double powi (double base, int exponent) {
   double result = 1.0;
   print_powi (base, exponent, result);
   if (exponent < 0) {
      base = 1.0 / base;
      exponent = - exponent;
      print_powi (base, exponent, result);
   }
   while (exponent > 0) {
      if (exponent % 2 == 0) { /* is even */
         base *= base;
         exponent /= 2;
      }else {
         result *= base;
         --exponent;
      }
      print_powi (base, exponent, result);
   }
   return result;
}

int main (int argc, char **argv) {
   vector<string> args (&argv[1], &argv[argc]);
   for (auto arg = args.cbegin(); arg != args.cend(); ++arg) {
      double base = from_string<double> (*arg);
      if (++arg == args.cend()) break;
      int exponent = from_string<int> (*arg);
      cout << endl << setprecision (DIGITS);
      double result = powi (base, exponent);
      cout << "ANSWER: " << base << " ** " << exponent 
           << " == " << result << endl;
   }
   return 0;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=powerint.out.grind \
//TEST//       powerint 2 2 2 9 2 15 2 16 2 24 \
//TEST//       >powerint.out 2>&1
//TEST// mkpspdf powerint.ps powerint.cpp* powerint.out*
*/

