// $Id: teststack.cpp,v 1.12 2014-04-15 19:16:24-07 - - $

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "iterstack.h"

int main (int argc, char **argv) {
   vector<string> args (&argv[1], &argv[argc]);
   
   iterstack<string> stk;
   for (const auto& arg: args) {
      cout << "Pushing: " << arg << endl;
      stk.push (arg);
   }
   for (const auto& elt: stk) cout << "Iteration: " << elt << endl;

   while (not stk.empty()) {
      cout << "Popping: " << stk.top() << endl;
      stk.pop();
   }
   return 0;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=teststack.out.grind \
//TEST//       teststack foo bar baz qux quux >teststack.out 2>&1
//TEST// mkpspdf teststack.ps iterstack.h teststack.cpp* teststack.out*
*/

