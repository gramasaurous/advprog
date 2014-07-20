// $Id: splitline.cpp,v 1.26 2014-04-24 14:18:14-07 - - $

//
// Illustrate splitting of input lines.
//

#include <iostream>
#include <string>
using namespace std;

string trim (const string &str) {
   size_t first = str.find_first_not_of (" \t");
   if (first == string::npos) return "";
   size_t last = str.find_last_not_of (" \t");
   return str.substr (first, last - first + 1);
}

int main() {
   for (;;) {
      string line;
      getline (cin, line);
      if (cin.eof()) break;
      cout << endl << "line  = \"" << line << "\"" << endl;
      line = trim (line);
      if (line.size() == 0 or line[0] == '#') {
         cout << "Comment or blank line." << endl;
         continue;
      }
      size_t pos = line.find_first_of ("=");
      if (pos == string::npos) {
         cout << "key   = \"" << line << "\"" << endl;
         cout << "No value in this line." << endl;
      }else {
         string key = trim (line.substr (0, pos == 0 ? 0 : pos - 1));
         string value = trim (line.substr (pos + 1));
         cout << "key   = \"" << key << "\"" << endl;
         cout << "value = \"" << value << "\"" << endl;
      }
   }
   return 0;
}

/*
//TEST// (echo '    # comment   ';
//TEST//  echo '                  ';
//TEST//  echo '    No equal in this line.           ';
//TEST//  echo '   key key key  =  value value value  ';
//TEST//  echo 'only key here =     ';
//TEST//  echo '  = only value here     ';
//TEST//  echo '   =   '
//TEST// ) | splitline >splitline.out 2>&1
//TEST// mkpspdf splitline.ps splitline.cpp* splitline.out
*/
