// $Id: cix-client.cpp,v 1.7 2014-07-25 12:12:51-07 - - $

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "cix_protocol.h"
#include "logstream.h"
#include "signal_action.h"
#include "sockets.h"

logstream log (cout);

unordered_map<string,cix_command> command_map {
   {"exit", CIX_EXIT},
   {"help", CIX_HELP},
   {"ls"  , CIX_LS  },
};

void cix_help() {
   static vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

void cix_ls (client_socket& server) {
   cix_header header;
   header.cix_command = CIX_LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.cix_command != CIX_LSOUT) {
      log << "sent CIX_LS, server did not return CIX_LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.cix_nbytes + 1];
      recv_packet (server, buffer, header.cix_nbytes);
      log << "received " << header.cix_nbytes << " bytes" << endl;
      buffer[header.cix_nbytes] = '\0';
      cout << buffer;
   }
}


void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

bool SIGINT_throw_cix_exit {false};
void signal_handler (int signal) {
   log << "signal_handler: caught " << strsignal (signal) << endl;
   switch (signal) {
      case SIGINT: case SIGTERM: SIGINT_throw_cix_exit = true; break;
      default: break;
   }
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   signal_action (SIGINT, signal_handler);
   signal_action (SIGTERM, signal_handler);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line);
         if (cin.eof()) throw cix_exit();
         if (SIGINT_throw_cix_exit) throw cix_exit();
         log << "command " << line << endl;
         const auto& itor = command_map.find (line);
         cix_command cmd = itor == command_map.end()
                         ? CIX_ERROR : itor->second;
         switch (cmd) {
            case CIX_EXIT:
               throw cix_exit();
               break;
            case CIX_HELP:
               cix_help();
               break;
            case CIX_LS:
               cix_ls (server);
               break;
            default:
               log << line << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}

