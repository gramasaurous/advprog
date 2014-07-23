// $Id: colornames.cpp,v 1.6 2014-05-02 17:07:18-07 - - $

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

#include "colornames.h"

#include "colortable.cppgen"

color::color (const string& name) {
   auto entry = color_names.find (name);
   if (entry != color_names.end()) {
      *this = entry->second;
   }else {
      invalid_argument error ("color::color(" + name + ")");
      if (name.size() != 8) throw error;
      string prefix = name.substr (0, 2);
      if (not (prefix == "0x" or prefix == "0X")) throw error;
cout<<"8";
      for (auto digit: name) if (not isxdigit(digit)) cout<<digit;
cout<<"9";
      for (size_t index = 0; index < 3; ++index) {
         string digit = name.substr (index * 2 + 2, 2);
         if (isspace (digit[0]) or isspace (digit[1])) throw error;
         ubvec[index] = stoul (digit, nullptr, 16);
      }
   }
}

color::operator string() const {
   ostringstream result ("0x");
   result << hex << setiosflags (ios::uppercase) << setfill ('0')
          << setw(2) << static_cast<unsigned> (red)
          << setw(2) << static_cast<unsigned> (green)
          << setw(2) << static_cast<unsigned> (blue);
   return result.str();
}

int main(int argc, char **argv) {
   vector<string> args (&argv[1], &argv[argc]);
   color c;
   cout << "&c=" << &c << endl;
   cout << "&c.ubvec=" << &c.ubvec << endl;
   cout << "&c.red=" << &c.red << endl;
   cout << "&c.green=" << &c.green << endl;
   cout << "&c.blue=" << &c.blue << endl;
   for (const auto& s: args) {
      try {
         color d (s);
         cout << s << "=" << string(d) << endl;
      }catch (invalid_argument& error) {
         cout << "invalid_argument(" << error.what() << ")" << endl;
      }
   }
   cout << 100 << endl;
   return 0;
}
