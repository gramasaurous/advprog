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
   DEBUGF('~',"f:"<<static_cast<unsigned>(big_value.front())<<endl);
   DEBUGF('~',"b"<<static_cast<unsigned>(big_value.back())<<endl);
   DEBUGF('~',"s"<<static_cast<unsigned>(big_value.size())<<endl);
}

//
// Addition/Subtraction
// do_bigadd() assumes top.size > bottom.size
//

bigint::bigvalue_t do_bigadd(const bigint::bigvalue_t& top,
      const bigint::bigvalue_t& bottom) {
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
   cout << "do_bigadd(): ";
   for (auto i : top) cout << static_cast<unsigned>(i);
   cout << " + ";
   for (auto i : bottom) cout << static_cast<unsigned>(i);
   cout << " = ";
   for (auto i : sum) cout << static_cast<unsigned>(i);
   cout << endl;

   for (auto i : sum) {
      if (i == 0) sum.pop_back();
      else break;
   }
   return sum;
}

bigint::bigvalue_t do_bigsub(const bigint::bigvalue_t& top,
      const bigint::bigvalue_t& bottom) {
   bigint::bigvalue_t diff{};
   auto itor_top = top.rbegin();
   auto itor_bottom = bottom.rbegin();

// use signed integers so we don't end up with -1 == 255
   int digit_top{0};
   int digit_bottom{0};
   int digit_diff{0};
   int borrow{0};

   while (itor_top != top.rend()) {
      digit_top = static_cast<int>(*itor_top++);
      if (itor_bottom  == bottom.rend()) {
         digit_bottom = 0;
      } else {
         digit_bottom = static_cast<int>(*itor_bottom++);
      }
      digit_top -= borrow;
      if (digit_top < digit_bottom) {
         borrow = 1;
         digit_top += 10;
      } else {
         borrow = 0;
      }
      digit_diff = digit_top - digit_bottom;
/*      cout << "do_bigsub():digit:"<< static_cast<unsigned>(digit_top);
      cout << " - " << static_cast<unsigned>(digit_bottom);
      cout << " = " << static_cast<unsigned>(digit_diff) << endl;*/
      diff.insert(diff.begin(), digit_diff);
   }
/*   cout << "do_bigsub(): ";
   for (auto i : top) cout << static_cast<unsigned>(i);
   cout << " - ";
   for (auto i : bottom) cout << static_cast<unsigned>(i);
   cout << " = ";
   for (auto i : diff) cout << static_cast<unsigned>(i);
   cout << endl;*/
   // Trim trailing zeros
   for (auto i : diff) {
      if (i == 0) diff.pop_back();
      else break;
   }
   return diff;
}

//
// do_bigless()
// returns true if left < right
// returns false if left > right or left == right
//
bool do_bigless (const bigint::bigvalue_t& left,
      const bigint::bigvalue_t& right) {
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
   bool right_is_less = do_bigless(right.big_value, left.big_value);
   if (left.negative == right.negative) {
      if (right_is_less) {
         sum.big_value = do_bigadd(left.big_value, right.big_value);
      } else {
         sum.big_value = do_bigadd(right.big_value, left.big_value);
      }
      sum.negative = left.negative;
   } else if (right_is_less) {
      sum.big_value = do_bigsub(left.big_value, right.big_value);
      sum.negative = true;
   } else {
      sum.big_value = do_bigsub(right.big_value, left.big_value);
      sum.negative = true;
   }
   //cout<<"operator+():"<<left<<" + "<< right << " = " << sum << endl;
   if (sum.big_value.size() == 0) sum.negative = false;
   return sum;
   //return left.long_value + right.long_value;
}

bigint operator- (const bigint& left, const bigint& right) {
   bigint diff{};
   bool right_is_less = do_bigless(right.big_value, left.big_value);
   if (left.negative == right.negative) {
      if (right_is_less) {
         diff.big_value = do_bigsub(left.big_value, right.big_value);
         diff.negative = left.negative;
      } else {
         diff.big_value = do_bigsub(right.big_value, left.big_value);
         diff.negative = !left.negative;
      }
   } else if (right_is_less) {
      diff.big_value = do_bigadd(left.big_value, right.big_value);
      diff.negative = true;
   } else {
      diff.big_value = do_bigadd(right.big_value, left.big_value);
      diff.negative = true;
   }   
   //cout<<"operator-():"<<left<<" - "<< right << " = " << diff << endl;
   if (diff.big_value.size() == 0) diff.negative = false;
   return (diff);
   //return left.long_value - right.long_value;
}

bigint operator+ (const bigint& right) {
   //return +right.long_value;
   return right;
}

bigint operator- (const bigint& right) {
   bool sign = right.negative;
   bigint retval = right;
   retval.negative = !sign;
   return retval;
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

bigint::bigvalue_t do_bigmult(const bigint::bigvalue_t& top,
      const bigint::bigvalue_t& bottom) {

   bigint::bigvalue_t product{};

   auto itor_bottom = bottom.rbegin();

   while (itor_bottom != bottom.rend()) {
      unsigned char carry {0};
      auto itor_top = top.rbegin();
      while (itor_top != top.rend()) {
         unsigned char digit = *itor_top++ * *itor_bottom++;
         digit += carry;
         product.insert(product.begin(), digit % 10);
         carry = digit / 10;
      }
   }
   return product;
}

//
// Multiplication algorithm.
//
bigint operator* (const bigint& left, const bigint& right) {
   //return left.long_value * right.long_value;
   bool right_is_less = do_bigless(right.big_value, left.big_value);
   bigint product {};
   if (right_is_less) {
      product.big_value = do_bigmult(left.big_value, right.big_value);
   } else {
      product.big_value = do_bigmult(right.big_value, left.big_value);
   }
   if (left.negative == right.negative) {
      product.negative = false;
   } else {
      product.negative = true;
   }
   return product;
}

//
// Division algorithm.
//

void multiply_by_2 (bigint& big) {
   big = big * 2;   
   return;
}

void divide_by_2 (bigint&) {
   return;
}



bigint::quot_rem divide (const bigint& left, const bigint& right) {
   if (right == 0) throw domain_error ("divide by 0");
   static bigint zero = 0;
   if (right == 0) throw domain_error ("bigint::divide");
   bigint divisor = right;
   bigint quotient = 0;
   bigint remainder = left;
   bigint power_of_2 = 1;
   while (do_bigless (divisor.big_value, remainder.big_value)) {
      multiply_by_2 (divisor);
      multiply_by_2 (power_of_2);
   }
   while (do_bigless (zero.big_value, power_of_2.big_value)) {
      if (not do_bigless (remainder.big_value, divisor.big_value)) {
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

bigint operator% (const bigint&, const bigint&) {
   //return divide (left, right).second;
   bigint that;
   return that;
}

bool operator== (const bigint& left, const bigint& right) {
   //return left.long_value == right.long_value;
   bool retval {true};
   if (left.negative != right.negative) {
      retval = false;
   } else if (left.big_value.size() != right.big_value.size()) {
      retval = false;
   } else {
      auto l = left.big_value.begin();
      auto r = right.big_value.begin();
      while (l != left.big_value.end()) {
         if (*l++ != *r++) {
            retval = false;
            break;
         }
      }
   }
   return retval;
}

bool operator< (const bigint& left, const bigint& right) {
   //return left.long_value < right.long_value;
   bool retval{true};
   if (left.negative != right.negative) {
      if (right.negative) retval = false;
   } else if (do_bigless(right.big_value, left.big_value)) {
      retval = false;
   }
   return retval;
}

ostream& operator<< (ostream& out, const bigint& that) {
   //out << that.long_value;
   int c{0};
   if (that.negative == true) {
      out << '-';
      ++c;
   }
   for (auto i : that.big_value) {
      if (c == 69) {
         c = 0;
         cout << "\\" << endl;
      } else {
         c++;
      }
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
