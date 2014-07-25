// Graham Greving
// ggreving@ucsc.edu
// util.cpp

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdexcept>
#include <string>
using namespace std;

#include "util.h"

int sys_info::exit_status = EXIT_SUCCESS;
string *sys_info::execname = NULL; // Must be initialized from main().

void sys_info_error (const string& condition) {
   throw logic_error ("main() has " + condition
               + " called sys_info::set_execname()");
}

void sys_info::set_execname (const string& argv0) {
   if (execname != NULL) sys_info_error ("already");
   int slashpos = argv0.find_last_of ('/') + 1;
   execname = new string (argv0.substr (slashpos));
   cout << boolalpha;
   cerr << boolalpha;
   TRACE ('u', "execname = " << execname);
}

const string& sys_info::get_execname () {
   if (execname == NULL) sys_info_error ("not yet");
   return *execname;
}

void sys_info::set_exit_status (int status) {
   if (execname == NULL) sys_info_error ("not yet");
   exit_status = status;
}

int sys_info::get_exit_status () {
   if (execname == NULL) sys_info_error ("not yet");
   return exit_status;
}

const string datestring () {
   time_t clock = time (NULL);
   struct tm *tm_ptr = localtime (&clock);
   char timebuf[256];
   strftime (timebuf, sizeof timebuf,
             "%a %b %e %H:%M:%S %Z %Y", tm_ptr);
   return timebuf;
}

list<string> split (const string& line, const string& delimiters) {
   list<string> words;
   size_t end = 0;
   // Loop over the string, splitting out words, and for each word
   // thus found, append it to the output list<string>.
   for (;;) {
      size_t start = line.find_first_not_of (delimiters, end);
      if (start == string::npos) break;
      end = line.find_first_of (delimiters, start);
      words.push_back (line.substr (start, end - start));
   }
   TRACE ('u', words);
   return words;
}

ostream& complain() {
   sys_info::set_exit_status (EXIT_FAILURE);
   cerr << sys_info::get_execname () << ": ";
   return cerr;
}

void syscall_error (const string& object) {
   complain() << object << ": " << strerror (errno) << endl;
}

string trim (const string &str) {
   size_t first = str.find_first_not_of (" \t");
   if (first == string::npos) return "";
   size_t last = str.find_last_not_of (" \t");
   return str.substr (first, last - first + 1);
}