// $Id: keyboard.cpp,v 1.12 2014-07-22 16:38:08-07 - - $

// Respond to keystrokes.

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>

unordered_map<int,string> special_keys {
   {GLUT_KEY_F1       , "GLUT_KEY_F1"       },
   {GLUT_KEY_F2       , "GLUT_KEY_F2"       },
   {GLUT_KEY_F3       , "GLUT_KEY_F3"       },
   {GLUT_KEY_F4       , "GLUT_KEY_F4"       },
   {GLUT_KEY_F5       , "GLUT_KEY_F5"       },
   {GLUT_KEY_F6       , "GLUT_KEY_F6"       },
   {GLUT_KEY_F7       , "GLUT_KEY_F7"       },
   {GLUT_KEY_F8       , "GLUT_KEY_F8"       },
   {GLUT_KEY_F9       , "GLUT_KEY_F9"       },
   {GLUT_KEY_F10      , "GLUT_KEY_F10"      },
   {GLUT_KEY_F11      , "GLUT_KEY_F11"      },
   {GLUT_KEY_F12      , "GLUT_KEY_F12"      },
   {GLUT_KEY_LEFT     , "GLUT_KEY_LEFT"     },
   {GLUT_KEY_UP       , "GLUT_KEY_UP"       },
   {GLUT_KEY_RIGHT    , "GLUT_KEY_RIGHT"    },
   {GLUT_KEY_DOWN     , "GLUT_KEY_DOWN"     },
   {GLUT_KEY_PAGE_UP  , "GLUT_KEY_PAGE_UP"  },
   {GLUT_KEY_PAGE_DOWN, "GLUT_KEY_PAGE_DOWN"},
   {GLUT_KEY_HOME     , "GLUT_KEY_HOME"     },
   {GLUT_KEY_END      , "GLUT_KEY_END"      },
   {GLUT_KEY_INSERT   , "GLUT_KEY_INSERT "  },
};

unordered_map<int,string> control_chars {
   {  0, "NUL"}, {  1, "SOH"}, {  2, "STX"}, {  3, "ETX"},
   {  4, "EOT"}, {  5, "ENQ"}, {  6, "ACK"}, {  7, "BEL"},
   {  8, "BS" }, {  9, "HT" }, { 10, "LF" }, { 11, "VT" },
   { 12, "FF" }, { 13, "CR" }, { 14, "SO" }, { 15, "SI" },
   { 16, "DLE"}, { 17, "DC1"}, { 18, "DC2"}, { 19, "DC3"},
   { 20, "DC4"}, { 21, "NAK"}, { 22, "SYN"}, { 23, "ETB"},
   { 24, "CAN"}, { 25, "EM" }, { 26, "SUB"}, { 27, "ESC"},
   { 28, "FS" }, { 29, "GS" }, { 30, "RS" }, { 31, "US" },
   {127, "DEL"},
};


using uchar = unsigned char;

// Characteristics of the window.
struct window {
   string name;
   int width {256};
   int height {192};
} window;

// Called by glutMainLoop to display window contents.
void display() {
   cout << __func__ << "()" << endl;
   glClearColor (0.25, 0.25, 0.25, 1.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
}

void print_special_key (int key) {
   const auto& keyname = special_keys.find (key);
   if (keyname == special_keys.end()) cout << "Unknown GLUT_KEY";
                                 else cout << keyname->second;
}

void print_keyboard_key (int key) {
   if (isgraph (key)) cout << "'" << (uchar)key << "'";
   else {
      const auto& control = control_chars.find (key);
      if (control != control_chars.end()) cout << control->second;
   }
}

void special (int key, int x, int y) {
   cout << __func__ << "(" << key << "," << x << "," << y << "): ";
   print_special_key (key);
   cout << endl;
}

void specialup (int key, int x, int y) {
   cout << __func__ << "(" << key << "," << x << "," << y << "): ";
   print_special_key (key);
   cout << endl;
}

void keyboard (uchar key, int x, int y) {
   cout << __func__ << "(" << (int)key << "," << x << "," << y << "): ";
   print_keyboard_key (key);
   cout << endl;
}

void keyboardup (uchar key, int x, int y) {
   cout << __func__ << "(" << (int)key << "," << x << "," << y << "): ";
   print_keyboard_key (key);
   cout << endl;
}


void reshape (int width, int height) {
   cout << __func__ << "(" << width << "," << height << ")" << endl;
   window.width = width;
   window.height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, window.width, 0, window.height, -1, +1);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window.width, window.height);
   glutPostRedisplay();
}

void close() {
   cout << __func__ << "()" << endl;
}

void entry (int state) {
   cout << __func__ << "(";
   switch (state) {
      case GLUT_LEFT: cout << "GLUT_LEFT"; break;
      case GLUT_ENTERED: cout << "GLUT_ENTERED"; break;
      default: cout << state; break;
   }
   cout << ")" << endl;
}

int main (int argc, char** argv) {
   window.name = basename (argv[0]);
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window.width, window.height);
   glutCreateWindow (window.name.c_str());
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   glutEntryFunc (entry);
   glutCloseFunc (close);
   glutKeyboardFunc (keyboard);
   glutKeyboardUpFunc (keyboardup);
   glutSpecialFunc (special);
   glutSpecialUpFunc (specialup);
   glutMainLoop();
   return 0;
}

