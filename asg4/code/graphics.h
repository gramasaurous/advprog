// Graham Greving
// ggreving@ucsc.edu
// asg4:graphics.h

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <memory>
#include <vector>
using namespace std;

#include <GL/freeglut.h>

#include "rgbcolor.h"
#include "shape.h"

class object {
   private:
      shared_ptr<shape> pshape;
      vertex center;
      rgbcolor color;
   public:
      // Default copiers, movers, dtor all OK.
      object(const shared_ptr<shape> &shape_ptr, const vertex &cen,
               const rgbcolor &col) {
         pshape = shape_ptr;
         center = cen;
         color = col;
      }
      void draw() { pshape->draw (center, color); }
      void draw(const rgbcolor &col) { pshape->draw (center, col); }
      void move (GLfloat delta_x, GLfloat delta_y) {
         center.xpos += delta_x;
         center.ypos += delta_y;
      }
};

class mouse {
      friend class window;
   private:
      int xpos {0};
      int ypos {0};
      int entered {GLUT_LEFT};
      int left_state {GLUT_UP};
      int middle_state {GLUT_UP};
      int right_state {GLUT_UP};
   private:
      void set (int x, int y) { xpos = x; ypos = y; }
      void state (int button, int state);
      void draw();
};


class window {
      friend class mouse;
   private:
      static int width;         // in pixels
      static int height;        // in pixels
      static vector<object> objects;
      static size_t selected_obj;
      static mouse mus;
      static float border_thickness;
      static rgbcolor border_color;
      static float move_by;
   private:
      static void close();
      static void entry (int mouse_entered);
      static void display();
      static void reshape (int width, int height);
      static void keyboard (GLubyte key, int, int);
      static void special (int key, int, int);
      static void motion (int x, int y);
      static void passivemotion (int x, int y);
      static void mousefn (int button, int state, int x, int y);
      static void select_object (int obj) {selected_obj = obj;};
      static void move_selected_object (float change_x, float change_y);
   public:
      static void push_back (const object& obj) {
                  objects.push_back (obj); }
      static void set_moveby(float move_by_) {move_by = move_by_;}
      static void setwidth (int width_) { width = width_; }
      static void setheight (int height_) { height = height_; }
      static void set_border(const rgbcolor& color, float thick) {
         border_thickness = thick;
         border_color = color;
      }
      static void main();
};

#endif

