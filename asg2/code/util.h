// $Id: util.h,v 1.5 2014-04-09 17:03:58-07 - - $

//
// util -
//    A utility class to provide various services not conveniently
//    included in other modules.
//

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

#include "debug.h"

//
// ydc_exn -
//    Indicate a problem where processing should be abandoned and
//    the main function should take control.
//

class ydc_exn: public runtime_error {
   public:
      explicit ydc_exn (const string& what);
};

//
// octal -
//    Convert integer to octal string.
//

const string octal (long decimal);


//
// sys_info -
//    Keep track of execname and exit status.  Must be initialized
//    as the first thing done inside main.  Main should call:
//       sys_info::execname (argv[0]);
//    before anything else.
//

class sys_info {
   private:
      static string execname_;
      static int status_;
   public:
      static void execname (const string& argv0);
      static const string& execname() {return execname_; }
      static void status (int status) {status_ = status; }
      static int status() {return status_; }
};

//
// complain -
//    Used for starting error messages.  Sets the exit status to
//    EXIT_FAILURE, writes the program name to cerr, and then
//    returns the cerr ostream.  Example:
//       complain() << filename << ": some problem" << endl;
//

ostream& complain();

//
// operator<< (vector) -
//    An overloaded template operator which allows vectors to be
//    printed out as a single operator, each element separated from
//    the next with spaces.  The item_t must have an output operator
//    defined for it.
//

template <typename item_t>
ostream& operator<< (ostream& out, const vector<item_t>& vec){
   string space = "";
   for (const auto& elem: vec) {
      out << space << elem; 
      space = " ";
   }
   return out;
}

#endif

