// Graham Greving
// ggreving@ucsc.edu
// asg2: bigint.cpp

#include <cstdlib>
#include <exception>
#include <limits>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"

bigint::bigint (long that): long_value (that) {
   DEBUGF ('~', this << " -> " << long_value)
}

bigint::bigint (const string& that) {
   auto itor = that.cbegin();
   //bool isnegative = false;
   if (itor != that.cend() and *itor == '_') {
      //isnegative = true;
      //++itor;
      negative = true;
      ++itor;
   }
   //int newval = 0;
   while (itor != that.end()) {
      //newval = newval * 10 + *itor++ - '0';
      big_value.push_back(*itor++ - '0');
   }
   //long_value = isnegative ? - newval : + newval;
   DEBUGF('~', "front: " << static_cast<unsigned>(big_value.front()) << endl);
   DEBUGF('~', "back: " << static_cast<unsigned>(big_value.back()) << endl);
   DEBUGF('~', "size: " << static_cast<unsigned>(big_value.size()) << endl);
}

//
// Addition/Subtraction
// do_bigadd() assumes top.size > bottom.size
//

bigint::bigvalue_t do_bigadd(const bigint::bigvalue_t& top, const bigint::bigvalue_t& bottom) {
   bigint::bigvalue_t sum{};        // return value
   bigint::digit_t digit_sum{0};    // digit marker
   bigint::digit_t digit_top{0};
   bigint::digit_t digit_bottom{0};
   bigint::digit_t carry{0};        // carryover marker

   // iterators
   auto itor_top = top.rbegin();
   auto itor_bottom = bottom.rbegin();

   while(itor_top != top.rend()) {
      digit_top = static_cast<unsigned>(*itor_top++);
      if (itor_bottom  == bottom.rend()) {
         digit_bottom = 0;
      } else {
         digit_bottom = static_cast<unsigned>(*itor_bottom++);
      }
      digit_sum = digit_bottom + digit_top + carry;
      if (digit_sum > 9) {
         carry = 1;
         digit_sum -= 10;
      } else {
         carry = 0;
      }
      sum.insert(sum.begin(), digit_sum);
   }
   return sum;
}

bigint::bigvalue_t do_bigsub(const bigint::bigvalue_t& top, const bigint::bigvalue_t& bottom) {
   bigint::bigvalue_t diff{};
   auto itor_top = top.rbegin();
   auto itor_bottom = bottom.rbegin();

   bigint::digit_t digit_top{0};
   bigint::digit_t digit_bottom{0};
   bigint::digit_t digit_diff{0};
   bigint::digit_t borrow{0};

   while (itor_top != top.rend()) {
      if (itor_bottom == bottom.rend()) {
         digit_bottom = 0;
      } else {
         digit_bottom = static_cast<unsigned>(*itor_bottom++);
      }
      if (borrow == 0) {
         digit_top = static_cast<unsigned>(*itor_top++);
      } else {
         digit_top = borrow;
         borrow = 0;
         itor_top++;
      }
      if (digit_top < digit_bottom) {
         borrow = *itor_top - 1; // already set to next digit
         digit_top += 10;
      }
      digit_diff = digit_top - digit_bottom;
      diff.insert(diff.begin(), digit_diff);
   }
   return diff;
}

//
// do_bigless()
// returns true if left < right
// returns false if left > right or left == right
//
bool do_bigless (const bigint::bigvalue_t& left, const bigint::bigvalue_t& right) {
   if (left.size() < right.size()) {
      return true;
   } else if (left.size() > right.size()) {
      return false;
   }

   auto itor_left = left.begin();
   auto itor_right = right.begin();

   while(itor_left != left.end() && itor_right != right.end()) {
      if (itor_left > itor_left) {
         return false;
      } else if (itor_left < itor_right) {
         return true;
      } else {
         itor_left++;
         itor_right++;
      }
   }
   return true;
}

bigint operator+ (const bigint& left, const bigint& right) {
   bigint sum{};
   if (left.negative == right.negative) {
      if (do_bigless(right.big_value, left.big_value)) {
         sum.big_value = do_bigadd(left.big_value, right.big_value);
      } else {
         sum.big_value = do_bigadd(right.big_value, left.big_value);
      }
      sum.negative = left.negative;
   } else if (do_bigless(left.big_value, right.big_value)) {
      sum.big_value = do_bigsub(right.big_value, left.big_value);
      sum.negative = true;
   } else {
      sum.big_value = do_bigsub(left.big_value, right.big_value);
      sum.negative = true;
   }
   cout << "operator+():" << left << " + " << right << " = " << sum << endl;
   return sum;
   //return left.long_value + right.long_value;
}

bigint operator- (const bigint& left, const bigint& right) {
   bigint diff{};
   
   diff.big_value = do_bigsub(left.big_value, right.big_value);
   
   cout << "operator-():" << left << " - " << right << " = " << diff << endl;
   return (diff);
   //return left.long_value - right.long_value;
}

bigint operator+ (const bigint& right) {
   return +right.long_value;
}

bigint operator- (const bigint& right) {
   //right.negative = true;
   //return (right);
   return -right.long_value;
}

long bigint::to_long() const {
   if (*this <= bigint (numeric_limits<long>::min())
    or *this > bigint (numeric_limits<long>::max()))
               throw range_error ("bigint__to_long: out of range");
   return long_value;
}

bool abs_less (const long& left, const long& right) {
   return left < right;
}



//
// Multiplication algorithm.
//
bigint operator* (const bigint& left, const bigint& right) {
   return left.long_value * right.long_value;
}

//
// Division algorithm.
//

void multiply_by_2 (bigint::unumber& unumber_value) {
   unumber_value *= 2;
}

void divide_by_2 (bigint::unumber& unumber_value) {
   unumber_value /= 2;
}



bigint::quot_rem divide (const bigint& left, const bigint& right) {
   if (right == 0) throw domain_error ("divide by 0");
   using unumber = unsigned long;
   static unumber zero = 0;
   if (right == 0) throw domain_error ("bigint::divide");
   unumber divisor = right.long_value;
   unumber quotient = 0;
   unumber remainder = left.long_value;
   unumber power_of_2 = 1;
   while (abs_less (divisor, remainder)) {
      multiply_by_2 (divisor);
      multiply_by_2 (power_of_2);
   }
   while (abs_less (zero, power_of_2)) {
      if (not abs_less (remainder, divisor)) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divide_by_2 (divisor);
      divide_by_2 (power_of_2);
   }
   return {quotient, remainder};
}

bigint operator/ (const bigint& left, const bigint& right) {
   return divide (left, right).first;
}

bigint operator% (const bigint& left, const bigint& right) {
   return divide (left, right).second;
}

bool operator== (const bigint& left, const bigint& right) {
   return left.long_value == right.long_value;
}

bool operator< (const bigint& left, const bigint& right) {
   return left.long_value < right.long_value;
}

ostream& operator<< (ostream& out, const bigint& that) {
   //out << that.long_value;
   if (that.negative == true) {
      out << '-';
   }
   for (auto i : that.big_value) {
      out << static_cast<unsigned>(i);
   }
   return out;
}

bigint pow (const bigint& base, const bigint& exponent) {
   DEBUGF ('^', "base = " << base << ", exponent = " << exponent);
   if (base == 0) return 0;
   bigint base_copy = base;
   long expt = exponent.to_long();
   bigint result = 1;
   if (expt < 0) {
      base_copy = 1 / base_copy;
      expt = - expt;
   }
   while (expt > 0) {
      if (expt & 1) { //odd
         result = result * base_copy;
         --expt;
      }else { //even
         base_copy = base_copy * base_copy;
         expt /= 2;
      }
   }
   DEBUGF ('^', "result = " << result);
   return result;
}
