// $Id: mousedepth.cpp,v 1.24 2014-05-12 18:51:37-07 - - $

#include <cmath>
#include <iostream>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>

struct {
   string name;
   int width {256};
   int height {192};
   int depth {64};
   int left_state {GLUT_UP};
} window;

struct color {
   GLubyte rgb[3];
};
const color red    {0xFF, 0x00, 0x00};
const color yellow {0xFF, 0xFF, 0x00};
const color green  {0x00, 0xFF, 0x00};

struct object {
   float xpos {0};
   float ypos {0};
   float zpos {0};
   color rgb = green;
   bool selected {false};
   void draw() {
      glPushMatrix();
      glBegin (GL_POLYGON);
      glColor3ubv (rgb.rgb);
      float wid = window.width / 10;
      float hgt = window.height / 10;
      float delta = 2 * M_PI / 64;
      for (float theta = 0; theta < 2 * M_PI; theta += delta) {
         float x = wid * cos (theta) + xpos;
         float y = hgt * sin (theta) + ypos;
         glVertex3f (x, y, zpos);
      }
      glEnd();
      glPopMatrix();
   }
} object;

void display() {
// cout << __func__ << "()" << endl;
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   object.draw();
   glutSwapBuffers();
}

void reshape (int width, int height) {
// cout << __func__ << "(" << width << "," << height << ")" << endl;
   window.width = width;
   window.height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, window.width, 0, window.height, 0, window.depth);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window.width, window.height);
   glClearColor (0.25, 0.25, 0.25, 1.0);
   object.xpos = window.width / 2;
   object.ypos = window.height / 2;
   object.rgb = green;
   glutPostRedisplay();
}

GLuint depth (int mouse_x, int mouse_y) {
// cout << __func__ << "(" << mouse_x << "," << mouse_y << ")" << endl;
   glEnable (GL_DEPTH_TEST);
   GLfloat scale, bias, depth;
   glGetFloatv (GL_DEPTH_SCALE, &scale);
   glGetFloatv (GL_DEPTH_BIAS, &bias);
   glReadPixels (mouse_x, window.height - mouse_y, 1, 1,
                 GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
   GLuint intdepth = lrintf (depth * window.depth);
// cout << "scale=" << scale
//      << ", bias=" << bias
//      << ", depth=" << depth
//      << ", intdepth=" << intdepth << endl;
   return intdepth;
}

void mouse (int button, int state, int mouse_x, int mouse_y) {
   (void) mouse_x; (void) mouse_y;
// cout << __func__ << "(" << button << "," << state << "," << mouse_x
//      << "," << mouse_y << ")" << endl;
   switch (button) {
      case GLUT_LEFT:
         window.left_state = state;
         break;
   }
   glutPostRedisplay();
}

void motion (int mouse_x, int mouse_y) {
   if (depth (mouse_x, mouse_y) != 0) object.rgb = green;
   else {
      object.rgb = red;
      object.xpos = mouse_x;
      object.ypos = window.height - mouse_y;
   }
   glutPostRedisplay();
}

void passivemotion (int mouse_x, int mouse_y) {
   if (depth (mouse_x, mouse_y) != 0) object.rgb = green;
                                 else object.rgb = yellow;
   glutPostRedisplay();
}

int main (int argc, char** argv) {
   window.name = basename (argv[0]);
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window.width, window.height);
   glutCreateWindow (window.name.c_str());
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   glutMouseFunc (mouse);
   glutMotionFunc (motion);
   glutPassiveMotionFunc (passivemotion);
   glutMainLoop();
   return 0;
}

