// Graham Greving
// ggreving@ucsc.edu
// trace.cpp

#include <climits>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#include "trace.h"

using boolvec = vector<char>;
boolvec traceflags::flags (UCHAR_MAX + 1, false);
const boolvec trueflags (UCHAR_MAX + 1, true);

void traceflags::setflags (const string& optflags) {
   for (char flag: optflags) {
      if (flag == '@') {
         flags = trueflags;
      }else {
         flags[flag] = true;
      }
   }
   // Note that TRACE can trace setflags.
   TRACE ('t',  "optflags = " << optflags);
}

//
// getflag -
//    Check to see if a certain flag is on.
//

bool traceflags::getflag (char flag) {
   // Bug alert:
   // Don't TRACE this function or the stack will blow up.
   bool result = flags[flag];
   return result;
}

