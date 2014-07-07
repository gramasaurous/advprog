// $Id: newtonsqrt.cpp,v 1.20 2014-04-09 18:01:19-07 - - $

//
// Newton's method to extract square root.
//

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

const double EPSILON = numeric_limits<double>::epsilon();
const double NOTNUMBER = numeric_limits<double>::quiet_NaN();
const int DIGITS = numeric_limits<double>::digits10 + 6;

bool are_close (double num1, double num2) {
   return fabs (num1 - num2) <= num1 * EPSILON;
}

double from_string (const string &arg) {
   stringstream stream {arg};
   double result{};
   if (stream >> result and stream.eof()) return result;
   return NOTNUMBER;
}


double newton_sqrt (double number) {
   if (number < 0) throw domain_error ("newton_sqrt");
   if (number == 0) return 0;
   if (std::isnan (number) or std::isinf (number)) return number;
   int exponent;
   double fraction = frexp (number, &exponent);
   cout << number << " = "
        << fraction << " * 2 ** " << exponent << endl;
   double guess = ldexp (fraction, exponent / 2);
   double result;
   for (int count = 0;; ++count) {
      cout << "approx(" << count << ") = " << guess << endl;
      result = (number / guess + guess) / 2.0;
      if (are_close (result, guess)) break;
      guess = result;
   }
   return result;
}

int main (int argc, char **argv) {
   cout << setprecision (DIGITS);
   for (int argi = 1; argi < argc; ++argi) {
      string arg = argv[argi];
      double number = from_string (arg);
      cout << endl << "argv[" << argi << "] = \"" << arg << "\" => "
           << number << endl;
      try {
         double value = newton_sqrt (number);
         cout << "sqrt (" << number << ") = " << value << endl;
      }catch (domain_error &error) {
         cout << "domain_error (" << error.what() << ")" << endl;
      }
   }
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=newtonsqrt.out.grind \
//TEST//       newtonsqrt 2 10 100 1000 1e6 1e1000 foo \
//TEST//       >newtonsqrt.out 2>&1
//TEST// mkpspdf newtonsqrt.ps newtonsqrt.cpp* newtonsqrt.out*
*/

