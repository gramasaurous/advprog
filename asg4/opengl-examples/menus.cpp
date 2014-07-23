// $Id: menus.cpp,v 1.4 2014-05-09 16:54:10-07 - - $

#include <cmath>
#include <map>
#include <iostream>
#include <string>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>

int window_width  = 256;
int window_height = 192;
string program_name;

enum shape_type {RECTANGLE, SQUARE, DIAMOND, ELLIPSE, CIRCLE};
map<shape_type,string> shape_map{
   {RECTANGLE, "Rectangle"},
   {SQUARE, "Square"},
   {DIAMOND, "Diamond"},
   {ELLIPSE, "Ellipse"},
   {CIRCLE, "Circle"},
};

void main_menu (int value) {
   cout << "main_menu(" << value << ")" << endl;
}

void shape_menu (int value) {
   shape_type shape = static_cast<shape_type> (value);
   cout << __func__ << "(" << value << ") [" << shape_map[shape]
        << "]" << endl;
}

void quit_menu (int value) {
    if (value) exit (0);
}


void createmenu() {
   int shape_menu_id = glutCreateMenu (shape_menu);
   cout << __func__ << ": shape_menu_id=" << shape_menu_id << endl;
   glutAddMenuEntry ("Rectangle", RECTANGLE);
   glutAddMenuEntry ("Square", SQUARE);
   glutAddMenuEntry ("Diamond", DIAMOND);
   glutAddMenuEntry ("Ellipse", ELLIPSE);
   glutAddMenuEntry ("Circle", CIRCLE);
   int quit_menu_id = glutCreateMenu (quit_menu);
   glutAddMenuEntry ("Confirm", true);
   glutAddMenuEntry ("Cancel", false);
   int main_menu_id = glutCreateMenu (main_menu);
   cout << __func__ << ": main_menu_id=" << main_menu_id << endl;
   glutAddSubMenu ("Draw", shape_menu_id);
   glutAddSubMenu ("Quit", quit_menu_id);
   glutAttachMenu (GLUT_LEFT_BUTTON);
}

void display() {
   glClear (GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
}

void reshape (int width, int height) {
   cout << width << "x" << height << endl;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window_width, 0, window_height);
   glClearColor (0.2, 0.2, 0.2, 1.0);
   glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char** argv) {
   program_name = basename (argv[0]);
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window_width, window_height);
   glutCreateWindow (program_name.c_str());
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   createmenu();
   glutMainLoop();
   return 0;
}

