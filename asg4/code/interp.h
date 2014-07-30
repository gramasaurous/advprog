// Graham Greving
// ggreving@ucsc.edu
// asg4:interp.h

#ifndef __INTERP_H__
#define __INTERP_H__

#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "debug.h"
#include "graphics.h"
#include "shape.h"

class interpreter {
   public:
      using shape_map = map<string,shape_ptr>;
      using parameters = vector<string>;
      using param = parameters::const_iterator;
      using range = pair<param,param>;
      void interpret (const parameters&);
      interpreter() {}
      ~interpreter();

   private:
      interpreter (const interpreter&) = delete;
      interpreter& operator= (const interpreter&) = delete;

      using interpreterfn = void (*) (param, param);
      using factoryfn = shape_ptr (*) (param, param);

      static map<string,interpreterfn> interp_map;
      static map<string,factoryfn> factory_map;
      static shape_map objmap;

      static void do_define (param begin, param end);
      static void do_draw (param begin, param end);

      static shape_ptr make_shape (param begin, param end);
      static shape_ptr make_text (param begin, param end);
      static shape_ptr make_ellipse (param begin, param end);
      static shape_ptr make_circle (param begin, param end);
      static shape_ptr make_polygon (param begin, param end);
      static shape_ptr make_rectangle (param begin, param end);
      static shape_ptr make_square (param begin, param end);
      static shape_ptr make_diamond (param begin, param end);
      static shape_ptr make_triangle (param begin, param end);
      static shape_ptr make_right_triangle (param begin, param end);
      static shape_ptr make_isosceles (param begin, param end);
      static shape_ptr make_line (param begin, param end);
};

#endif

