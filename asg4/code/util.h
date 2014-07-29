// Graham Greving
// ggreving@ucsc.edu
// asg4:util.h

//
// util -
//    A utility class to provide various services not conveniently
//    included in other modules.
//

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#include "debug.h"

//
// sys_info -
//    Keep track of execname and exit status.  Must be initialized
//    as the first thing done inside main.  Main should call:
//       sys_info::execname (argv[0]);
//    before anything else.
//

class sys_info {
   friend int main (int argc, char** argv);
   private:
      static string execname_;
      static int exit_status_;
      static void execname (const string& argv0);
   public:
      static const string& execname();
      static void exit_status (int status);
      static int exit_status();
};

//
// datestring -
//    Return the current date, as printed by date(1).
//

const string datestring();


//
// split -
//    Split a string into a vector<string>..  Any sequence
//    of chars in the delimiter string is used as a separator.  To
//    Split a pathname, use "/".  To split a shell command, use " ".
//

vector<string> split (const string& line, const string& delimiter);

//
// complain -
//    Used for starting error messages.  Sets the exit status to
//    EXIT_FAILURE, writes the program name to cerr, and then
//    returns the cerr ostream.  Example:
//       complain() << filename << ": some problem" << endl;
//

ostream& complain();

//
// syscall_error -
//    Complain about a failed system call.  Argument is the name
//    of the object causing trouble.  The extern errno must contain
//    the reason for the problem.
//

void syscall_error (const string&);

//
// operator<< (vector) -
//    An overloaded template operator which allows vectors to be
//    printed out as a single operator, each element separated from
//    the next with spaces.  The item_t must have an output operator
//    defined for it.
//


template <typename item_t>
ostream& operator<< (ostream& out, const vector<item_t>& vec);

//
// operator<< (pair<iterator,iterator>) -
//    Allow a pair of iterators to be passed in and print all of the
//    values between the begin and end pair.
//

template <typename iterator>
ostream& operator<< (ostream& out, pair<iterator,iterator> range);

//
// string to_string (thing) -
//    Convert anything into a string if it has an ostream<< operator.
//

template <typename type>
string to_string (const type&);

//
// thing from_string (cons string&) -
//    Scan a string for something if it has an istream>> operator.
//

template <typename result_t>
result_t from_string (const string&);

//
// Demangle a C++ class name.
//
template <typename type>
string demangle (const type& object);

#include "util.tcc"
#endif


