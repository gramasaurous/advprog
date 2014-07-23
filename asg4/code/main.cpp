// $Id: main.cpp,v 1.13 2014-05-08 18:32:56-07 - - $

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

#include "debug.h"
#include "graphics.h"
#include "interp.h"
#include "util.h"

//
// Parse a file.  Read lines from input file, parse each line,
// and interpret the command.
//

void parsefile (const string& infilename, istream& infile) {
   interpreter::shape_map shapemap;
   interpreter interp;
   for (int linenr = 1;; ++linenr) {
      try {
         string line;
         getline (infile, line);
         if (infile.eof()) break;
         if (line.size() == 0) continue;
         for (;;) {
            DEBUGF ('m', line);
            int last = line.size() - 1;
            if (line[last] != '\\') break;
            line[last] = ' ';
            string contin;
            getline (infile, contin);
            if (infile.eof()) break;
            line += contin;
         }
         interpreter::parameters words = split (line, " \t");
         if (words.size() == 0 or words.front()[0] == '#') continue;
         DEBUGF ('m', words);
         interp.interpret (words);
      }catch (runtime_error error) {
         complain() << infilename << ":" << linenr << ": "
                    << error.what() << endl;
      }
   }
   DEBUGF ('m', infilename << " EOF");
}


//
// Scan the option -@ and check for operands.
//

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:w:h:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         case 'w':
            window::setwidth (stoi (optarg));
            break;
         case 'h':
            window::setheight (stoi (optarg));
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

//
// Main function.  Iterate over files if given, use cin if not.
//
int main (int argc, char** argv) {
   sys_info::execname (argv[0]);
   scan_options (argc, argv);
   vector<string> args (&argv[optind], &argv[argc]);
   if (args.size() == 0) {
      parsefile ("-", cin);
   }else if (args.size() > 1) {
      cerr << "Usage: " << sys_info::execname() << "-@flags"
           << "[filename]" << endl;
   }else {
      const string infilename = args[0];
      ifstream infile (infilename.c_str());
      if (infile.fail()) {
         syscall_error (infilename);
      }else {
         DEBUGF ('m', infilename << "(opened OK)");
         parsefile (infilename, infile);
         // fstream objects auto closed when destroyed
      }
   }
   int status = sys_info::exit_status();
   if (status != 0) return status;
   window::main();
   return 0;
}

