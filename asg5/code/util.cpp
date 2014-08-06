// Graham Greving
// ggreving@ucsc.edu
// asg4:util.cpp

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
using namespace std;

#include "util.h"

vector<string> split (const string& line, const string& delimiters) {
   vector<string> words;
   int end = 0;
   for (;;) {
      size_t start = line.find_first_not_of (delimiters, end);
      if (start == string::npos) break;
      end = line.find_first_of (delimiters, start);
      words.push_back (line.substr (start, end - start));
   }
   return words;
}
