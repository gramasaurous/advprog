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

//
// split -
//    Split a string into a vector<string>..  Any sequence
//    of chars in the delimiter string is used as a separator.  To
//    Split a pathname, use "/".  To split a shell command, use " ".
//

vector<string> split (const string& line, const string& delimiter);

#endif


