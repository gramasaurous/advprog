// Graham Greving
// ggreving@ucsc.edu
// main.cpp

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_pair = xpair<const string,string>;
using str_str_map = listmap<string,string>;

// returns position of first non-option argument
int scan_options (int argc, char** argv) {
   opterr = 0;
   int c{0};
   for (;;) {
      c++;
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
   return c;
}

int do_line(string line) {
   line = trim (line);
   if (line.size() == 0 or line[0] == '#') {
      cout << "Comment or blank line." << endl;
      return 0;
   }
   size_t pos = line.find_first_of ("=");
   if (pos == string::npos) {
      //cout << "key   = \"" << line << "\"" << endl;
      //cout << "No value in this line." << endl;
      cout << "do_find(key)" << endl;
   } else {
      string key = trim (line.substr (0, pos == 0 ? 0 : pos - 1));
      string value = trim (line.substr (pos + 1));
      bool k = (key.size() == 0); // true if no key
      bool v = (value.size() == 0); // true if no value

      //cout << "key   = \"" << key << "\"" << endl;
      //cout << "value = \"" << value << "\"" << endl;
      if (k == true && v == true) { // no key
         cout << "do_printall()" << endl;
      } else if (v == true) { // key, but no value
         cout << "do_delete(key)" << endl;
      } else {                // both value and key given
         cout << "do_insert(key, value)" << endl;
      }
   }
   return 0;
}

void do_file(const string& filename, istream& input) {
   for (int lcount = 1;; ++lcount) {
      string line;
      getline(input, line);
      if (input.eof()) break;
      else {
         do_line(line);
      }
   }
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   int file_pos = scan_options (argc, argv);

   str_str_map test;
   for (int argi = file_pos; argi < argc; ++argi) {
      string filename = argv[argi];
      if (filename == "-") do_file(filename, cin);
      else {
         ifstream file_in(filename);
         if (! file_in.fail()) do_file(filename, file_in);
         else complain() << "file not found." << endl;
      }
   }

   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   test.erase (itor);

   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

