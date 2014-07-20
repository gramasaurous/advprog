// Graham Greving
// ggreving@ucsc.edu
// asg2: scanner.cpp

#include <iostream>
#include <locale>
using namespace std;

#include "scanner.h"
#include "debug.h"

scanner::scanner() {
   seen_eof = false;
   advance();
}

void scanner::advance() {
   if (not seen_eof) {
      cin.get (lookahead);
      if (cin.eof()) seen_eof = true;
   }
}

token_t scanner::scan() {
   token_t result;
   while ( !seen_eof && isspace (lookahead) ) advance();
   if (seen_eof) {
      result.symbol = SCANEOF;
   } else if (lookahead == '_' || isdigit (lookahead)) {
      result.symbol = NUMBER;
      do {
         result.lexinfo += lookahead;
         advance();
      } while ( !seen_eof && isdigit (lookahead) );
   } else {
      result.symbol = OPERATOR;
      result.lexinfo += lookahead;
      advance();
   }
   DEBUGF ('S', result);
   return result;
}

ostream& operator<< (ostream& out, const terminal_symbol& symbol) {
   switch (symbol) {
      case NUMBER  : out << "NUMBER"  ; break;
      case OPERATOR: out << "OPERATOR"; break;
      case SCANEOF : out << "SCANEOF" ; break;
   }
   return out;
}

ostream& operator<< (ostream& out, const token_t& token) {
   out << token.symbol << ": \"" << token.lexinfo << "\"";
   return out;
}

