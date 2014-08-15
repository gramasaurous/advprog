// Graham Greving
// ggreving@ucsc.edu
// asg5: signal_action.h

#ifndef __SIGNAL_ACTION_H__
#define __SIGNAL_ACTION_H__

#include <stdexcept>
using namespace std;

#include <signal.h>

class cix_exit: public exception{};

class signal_action {
   private:
      struct sigaction action;
   public:
      signal_action (int signal, void (*handler) (int));
};

class signal_error: runtime_error {
   public:
      int signal;
      explicit signal_error (int signal);
};

#endif

