// $Id: division.cpp,v 1.6 2014-05-29 19:11:29-07 - - $

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

using ulong = unsigned long;
using uupair = pair<ulong,ulong>;

uupair divide (const ulong &dividend, const ulong &divisor) {
   if (divisor == 0) throw domain_error ("divide(_,0)");
   ulong powerof2 = 1;
   ulong divisor_ = divisor;
   while (divisor_ < dividend) {
      divisor_ *= 2;
      powerof2 *= 2;
   }
   ulong quotient = 0;
   ulong remainder = dividend;
   while (powerof2 > 0) {
      if (divisor_ <= remainder) {
         remainder -= divisor_;
         quotient += powerof2;
      }
      divisor_ /= 2;
      powerof2 /= 2;
   }
   return uupair (quotient, remainder);
}


ostream &operator<< (ostream &out, const uupair &pair) {
   out << pair.first << " R " << pair.second;
   return out;
}

uupair tests[] = {
   {             0L, 1024L},
   {             5L,    7L},
   {           100L,    0L},
   {           100L,   50L},
   {           320L,   20L},
   {           963L,   71L},
   {12345678912345L, 9876L},
};

int main (int argc, char **argv) {
   (void) argc; // warning: unused parameter 'argc'
   (void) argv; // warning: unused parameter 'argv'
   uupair *testend = tests + sizeof tests / sizeof *tests;
   for (uupair *itor = tests; itor < testend; ++itor) {
      ulong dividend = itor->first;
      ulong divisor = itor->second;
      cout << dividend << " / " << divisor << " = ";
      try {
         uupair result = divide (dividend, divisor);
         cout << result;
         uupair tested = uupair (dividend / divisor,
                                 dividend % divisor);
         if (tested != result) {
            cout << ": wrong " << tested;
         }
      }catch (domain_error &error) {
         cout << "domain_error: " << error.what();
      }
      cout << endl;
   }
   return EXIT_SUCCESS;
}

//TEST// ./division 2>&1 >division.output
//TEST// mkpspdf division.ps division.cpp* division.output

