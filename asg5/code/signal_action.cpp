// $Id: signal_action.cpp,v 1.6 2014-05-27 17:16:42-07 - - $

#include <cstring>
#include <string>
#include <unordered_map>
using namespace std;

#include "signal_action.h"

signal_action::signal_action (int signal, void (*handler) (int)) {
   action.sa_handler = handler;
   sigfillset (&action.sa_mask);
   action.sa_flags = 0;
   int rc = sigaction (signal, &action, nullptr);
   if (rc < 0) throw signal_error (signal);
}

signal_error::signal_error (int signal):
              runtime_error (string ("signal_error(")
                             + strsignal (signal) + ")"),
              signal(signal) {}

