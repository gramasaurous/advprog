// $Id: translate.cpp,v 1.32 2014-05-08 22:00:26-07 - - $

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>

struct {
   string name;
   int width;
   int height;
} window;

struct rgbcolor {
   union { 
      GLubyte ubvec[3];
      struct {
         GLubyte red;
         GLubyte green;
         GLubyte blue;
      };
   };
};
const rgbcolor Red     {0xFF, 0x00, 0x00};
const rgbcolor Green   {0x00, 0xFF, 0x00};
const rgbcolor Blue    {0x00, 0x00, 0xFF};
const rgbcolor Cyan    {0x00, 0xFF, 0xFF};
const rgbcolor Magenta {0xFF, 0x00, 0xFF};
const rgbcolor Yellow  {0xFF, 0xFF, 0x00};
const rgbcolor White   {0xFF, 0xFF, 0xFF};
const rgbcolor Black   {0x00, 0x00, 0x00};

string to_string (const rgbcolor& color) {
   ostringstream result; 
   result << "0x" 
          << hex << setiosflags (ios::uppercase) << setfill ('0')
          << setw(2) << (unsigned) color.red
          << setw(2) << (unsigned) color.green
          << setw(2) << (unsigned) color.blue;
   return result.str();
}


void draw_rectangle (const rgbcolor& color, const string& name,
                     GLfloat xcenter, GLfloat ycenter) {
   cout << __func__ << "(" << to_string (color) << ", "
        << xcenter << ", " << ycenter << ")" << endl;
   GLfloat delta_x = window.width / 8;
   GLfloat delta_y = window.height / 4;
   glPushMatrix();
   glTranslatef (xcenter,  ycenter, 0);
   glBegin (GL_POLYGON);
   glColor3ubv (color.ubvec);
   glVertex2f (-delta_x, -delta_y);
   glVertex2f (+delta_x, -delta_y);
   glVertex2f (+delta_x, +delta_y);
   glVertex2f (-delta_x, +delta_y);
   glEnd();
   rgbcolor inverse = {(GLubyte) (0xFF - color.red),
                       (GLubyte) (0xFF - color.green),
                       (GLubyte) (0xFF - color.blue)};
   glColor3ubv (inverse.ubvec);
   void* font = GLUT_BITMAP_TIMES_ROMAN_24;
   float xpos = - glutBitmapLength (font, (GLubyte*) name.c_str()) / 2;
   float ypos = - glutBitmapHeight (font) / 2;
   glRasterPos2f (xpos, ypos);
   glutBitmapString (font, (GLubyte*) name.c_str());
   glPopMatrix();
   glutSwapBuffers();
}

void display() {
   GLfloat width = window.width;
   GLfloat height = window.height;
   glClear (GL_COLOR_BUFFER_BIT);
   draw_rectangle (Red    , "Red"    ,  width * 0.125, height * 0.75);
   draw_rectangle (Green  , "Green"  ,  width * 0.375, height * 0.75);
   draw_rectangle (Blue   , "Blue"   ,  width * 0.625, height * 0.75);
   draw_rectangle (White  , "White"  ,  width * 0.875, height * 0.75);
   draw_rectangle (Cyan   , "Cyan"   ,  width * 0.125, height * 0.25);
   draw_rectangle (Magenta, "Magenta",  width * 0.375, height * 0.25);
   draw_rectangle (Yellow , "Yellow" ,  width * 0.625, height * 0.25);
   draw_rectangle (Black  , "Black"  ,  width * 0.875, height * 0.25);
}


void reshape (int width, int height) {
   cout << __func__ << "(" << width << ", " << height << ")" << endl;
   window.width = width;
   window.height = height;
   ostringstream title;
   title << window.name << "(" << window.width << ","
         << window.height << ")";
   glutSetWindowTitle (title.str().c_str());
   glutSetIconTitle (title.str().c_str());
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window.width, 0, window.height);
   glViewport (0, 0, window.width, window.height);
   glClearColor (0.5, 0.5, 0.5, 1.0);
}

int main (int argc, char** argv) {
   window.name = basename (argv[0]);
   glutInit (&argc, argv);
   glutInitWindowSize (480, 360);
   glutCreateWindow (window.name.c_str());
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   glutMainLoop();
   return 0;
}
