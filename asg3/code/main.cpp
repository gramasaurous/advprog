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

void do_insert() {

}

void do_file(string filename, istream& input, str_str_map& m) {
   for (int lcount = 1;; ++lcount) {
      string line;
      getline(input, line);
      if (input.eof()) break;
      else {
         cout << filename << ": " << lcount << ": " << line << endl;
         line = trim (line);
         if (line.size() == 0 or line[0] == '#') {
            cout << "Comment or blank line." << endl;
            return;
         }
         size_t pos = line.find_first_of ("=");
         if (pos == string::npos) {
            //cout << "key   = \"" << line << "\"" << endl;
            //cout << "No value in this line." << endl;
            cout << "do_find(key)" << endl;
         } else {
            string key=trim (line.substr (0, pos == 0 ? 0 : pos - 1));
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
               cout << "do_insert(" << key << ", " << value
                  << ")" << endl;
               str_str_pair pair(key,value);
               m.insert(pair);
            }
         }
      }
   }
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);

   str_str_map m;
   int file_pos = scan_options (argc, argv);
   if (file_pos >= argc) {
      do_file("-", cin, m);
   } else {
      for (int argi = file_pos; argi < argc; ++argi) {
         string filename = argv[argi];
         if (filename == "-") {
            do_file("-", cin, m);
         } else {
            ifstream file_in(filename);
            if (! file_in.fail()) {
               do_file(filename, file_in, m);
            } else complain() << "File:" << filename <<
               " does not exist." << endl;
         }
      }      
   }

   //str_str_map test;
   for (str_str_map::iterator itor = m.begin();
        itor != m.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = m.begin();
   m.erase (itor);

   return EXIT_SUCCESS;
}

