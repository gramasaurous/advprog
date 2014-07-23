// $Id: ellipses.cpp,v 1.8 2014-07-22 16:38:06-07 - - $

// Draw several ellipses in window.

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>

using uchar = unsigned char;

// Characteristics of the window.
struct window {
   string name;
   int width {512};
   int height {384};
} window;

const uchar RED[] = {0xFF, 0x00, 0x00};
const uchar CYAN[] = {0x00, 0xFF, 0xFF};
const uchar BLUE[] = {0x00, 0x00, 0xFF};
const uchar YELLOW[] = {0xFF, 0xFF, 0x00};

void draw_ellipse (int kind, const uchar* color, float scale) {
   glBegin (kind);
   glEnable (GL_LINE_SMOOTH);
   glColor3ubv (color);
   const float delta = 2 * M_PI / 32;
   float width = window.width / 3 * scale;
   float height = window.height / 3 * scale;
   for (float theta = 0; theta < 2 * M_PI; theta += delta) {
      float xpos = width * cos (theta) + window.width / 2;
      float ypos = height * sin (theta) + window.height / 2;
      glVertex2f (xpos, ypos);
   }
   glEnd();
}

// Called by glutMainLoop to display window contents.
void display() {
   cout << __func__ << "()" << endl;
   glClearColor (0.25, 0.25, 0.25, 1.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glLineWidth (4);
   draw_ellipse (GL_POLYGON, CYAN, 1.0);
   draw_ellipse (GL_LINE_LOOP, RED, 1.0);
   draw_ellipse (GL_POLYGON, YELLOW, 0.5);
   draw_ellipse (GL_LINE_LOOP, BLUE, 0.5);
   glutSwapBuffers();
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
   glutInitWindowPosition (128, 128);
   glutCreateWindow (window.name.c_str());
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   glutEntryFunc (entry);
   glutCloseFunc (close);
   glutMainLoop();
   return 0;
}

//TEST// mkpspdf hello-gl.ps hello-gl.cpp*
