// $Id: cix_protocol.h,v 1.4 2014-05-28 12:23:46-07 - - $

#ifndef __CIX_PROTOCOL__H__
#define __CIX_PROTOCOL__H__

#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std;

#include "sockets.h"

enum cix_command {CIX_ERROR = 0, CIX_EXIT,
                  CIX_GET, CIX_HELP, CIX_LS, CIX_PUT, CIX_RM,
                  CIX_FILE, CIX_LSOUT, CIX_ACK, CIX_NAK};

size_t constexpr CIX_FILENAME_SIZE = 59;
struct cix_header {
   uint32_t cix_nbytes {0};
   uint8_t cix_command {0};
   char cix_filename[CIX_FILENAME_SIZE] {};
};

void send_packet (base_socket& socket,
                  const void* buffer, size_t bufsize);

void recv_packet (base_socket& socket, void* buffer, size_t bufsize);

ostream& operator<< (ostream& out, const cix_header& header);

string get_cix_server_host (const vector<string>& args, size_t index);

in_port_t get_cix_server_port (const vector<string>& args,
                               size_t index);

#endif

