// Graham Greving
// ggreving@ucsc.edu
// asg4:debug.cpp

#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#include "debug.h"
#include "util.h"

vector<bool> debugflags::flags (UCHAR_MAX + 1, false);

void debugflags::setflags (const string& initflags) {
   for (const char flag: initflags) {
      if (flag == '@') flags.assign (flags.size(), true);
                  else flags[flag] = true;
   }
   // Note that DEBUGF can trace setflags.
   if (getflag ('x')) {
      string flag_chars;
      for (size_t index = 0; index < flags.size(); ++index) {
         if (getflag (index)) flag_chars += (char) index;
      }
   }
}

//
// getflag -
//    Check to see if a certain flag is on.
//

bool debugflags::getflag (char flag) {
   // WARNING: Don't TRACE this function or the stack will blow up.
   unsigned uflag = (unsigned char) flag;
   assert (uflag < flags.size());
   return flags[uflag];
}

void debugflags::where (char flag, const char* file, int line,
                        const char* func) {
   cout << sys_info::execname() << ": DEBUG(" << flag << ") "
        << file << "[" << line << "] " << func << "()" << endl;
}

