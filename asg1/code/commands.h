// $Id: commands.h,v 1.8 2014-06-11 13:49:31-07 - - $

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <map>
using namespace std;
// in a library header, don't do this
// but this is a project header, so it's OK
// library files are included before user header files
#include "inode.h"
#include "util.h"

//
// A couple of convenient usings to avoid verbosity.
// using == typedef
//

using command_fn = void (*)(inode_state& state, const wordvec& words);
using command_map = map<string,command_fn>;

//
// commands -
//    A class to hold and dispatch each of the command functions.
//    Each command "foo" is interpreted by a command_fn fn_foo.
// ctor -
//    The default ctor initializes the map.
// operator[] -
//    Given a string, returns a command_fn associated with it,
//    or 0 if not found.
//

class commands {
   private:
      commands (const inode&) = delete; // copy ctor
      commands& operator= (const inode&) = delete; // operator=
      command_map map;
   public:
      commands(); // default constructor
      command_fn at (const string& cmd);
};


//
// execution functions -
//    See the man page for a description of each of these functions.
//

void fn_cat    (inode_state& state, const wordvec& words);
void fn_cd     (inode_state& state, const wordvec& words);
void fn_echo   (inode_state& state, const wordvec& words);
void fn_exit   (inode_state& state, const wordvec& words);
void fn_ls     (inode_state& state, const wordvec& words);
void fn_lsr    (inode_state& state, const wordvec& words);
void fn_make   (inode_state& state, const wordvec& words);
void fn_mkdir  (inode_state& state, const wordvec& words);
void fn_prompt (inode_state& state, const wordvec& words);
void fn_pwd    (inode_state& state, const wordvec& words);
void fn_rm     (inode_state& state, const wordvec& words);
void fn_rmr    (inode_state& state, const wordvec& words);

//
// exit_status_message -
//    Prints an exit message and returns the exit status, as recorded
//    by any of the functions.
//

int exit_status_message();
class ysh_exit_exn: public exception {};

#endif

