// Graham Greving
// ggreving@ucsc.edu
// asg4:interp.cpp

#include <map>
#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <GL/freeglut.h>

#include "debug.h"
#include "interp.h"
#include "shape.h"
#include "util.h"

map<string,interpreter::interpreterfn> interpreter::interp_map {
   {"define" , &interpreter::do_define },
   {"draw"   , &interpreter::do_draw   },
   {"border" , &interpreter::do_border },
};

map<string,interpreter::factoryfn> interpreter::factory_map {
   {"text"           , &interpreter::make_text           },
   {"ellipse"        , &interpreter::make_ellipse        },
   {"circle"         , &interpreter::make_circle         },
   {"polygon"        , &interpreter::make_polygon        },
   {"rectangle"      , &interpreter::make_rectangle      },
   {"square"         , &interpreter::make_square         },
   {"diamond"        , &interpreter::make_diamond        },
   {"triangle"       , &interpreter::make_triangle       },
   {"right_triangle" , &interpreter::make_right_triangle },
   {"isosceles"      , &interpreter::make_isosceles      },
   {"equilateral"    , &interpreter::make_equilateral    }   
};

interpreter::shape_map interpreter::objmap;

interpreter::~interpreter() {
   for (const auto& itor: objmap) {
      cout << "objmap[" << itor.first << "] = "
           << *itor.second << endl;
   }
}

void interpreter::interpret (const parameters& params) {
   DEBUGF ('i', params);
   param begin = params.cbegin();
   string command = *begin;
   DEBUGF('i', command);
   auto itor = interp_map.find (command);
   if (itor == interp_map.end()) throw runtime_error ("syntax error");

   interpreterfn func = itor->second;
   for (auto i = begin; i != params.cend(); ++i) {
      cout << *i << " ";
   } cout << endl;
   func (++begin, params.cend());
}

void interpreter::do_border (param begin, param end) {
   if ((end - begin) != 2) throw runtime_error("syntax error");
   rgbcolor color{*begin++};
   float thickness = stod(*begin);
   window::set_border(color,thickness);
}

void interpreter::do_define (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string name = *begin;
   DEBUGF ('t', name);
   objmap.insert ({name, make_shape (++begin, end)});
}


void interpreter::do_draw (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if (end - begin != 4) throw runtime_error ("syntax error");
   string name = begin[1];
   shape_map::const_iterator itor = objmap.find (name);
   if (itor == objmap.end()) {
      throw runtime_error (name + ": no such shape");
   }
   vertex where {from_string<GLfloat> (begin[2]),
                 from_string<GLfloat> (begin[3])};
   rgbcolor color {begin[0]};
   object new_obj(itor->second, where, color);
   window::push_back(new_obj);
   //itor->second->draw (where, color);
}

/*
   make_shape_X() functions
   initialize a shared_ptr<shape_X>
   with the passed in parameters
*/

shape_ptr interpreter::make_shape (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string type = *begin++;
   auto itor = factory_map.find(type);
   if (itor == factory_map.end()) {
      throw runtime_error (type + ": no such shape");
   }
   factoryfn func = itor->second;
   return func (begin, end);
}

// need to write these fn declarations
shape_ptr interpreter::make_text (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string font = *begin;
   string data{};
   for (++begin; begin != end; ++begin) {
      DEBUGF ('t', *begin);
      data += *begin + " ";
   }
   return make_shared<text> (font, data);
}

shape_ptr interpreter::make_ellipse (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if ((end - begin) != 2) throw runtime_error("syntax error: ellipse");
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<ellipse> (width, height);
}

shape_ptr interpreter::make_circle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if ((end - begin) != 1) throw runtime_error("syntax error: circle");
   return make_shared<circle> (GLfloat(stod(*begin)));
}

shape_ptr interpreter::make_polygon (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if (((end - begin) % 2) != 0) {
      throw runtime_error ("syntax error: polygon");
   }
   float x_avg{};
   float y_avg{};
   int v_count{0};
   vector<vertex> v_list;

   for (auto i = begin; i != end; i++) {
      GLfloat xpos = stod(*i++);
      GLfloat ypos = stod(*i);
      x_avg += xpos;
      y_avg += ypos;
      vertex v{xpos, ypos};
      v_count++;
      v_list.push_back(v);
   }
   if (v_count == 0) throw runtime_error ("syntax error: no vertices");
   x_avg /= v_count;
   y_avg /= v_count;
   DEBUGF ('p', "avg: (" << x_avg << "," << y_avg << ")");
   // Normalize the vertices (subtract avg)
   for (auto v = v_list.begin(); v != v_list.end(); ++v) {
      v->xpos -= x_avg;
      v->ypos -= y_avg;
   }
   // Here, all vertices exist around center 0,0
   // We will now sort them by their angle to the x-axis using
   // atan2(ypos,xpos) from cmath
   std::sort (v_list.begin(), v_list.end(),
      [](const vertex &a, const vertex &b){
      float degree_a = atan2(a.ypos, a.xpos) * 180 / M_PI;
      float degree_b = atan2(b.ypos, b.xpos) * 180 / M_PI;
      //if (degree_a == degree_b) return (a.ypos < b.ypos);
      return (degree_a < degree_b);
   });
   cout << "v_list sorted." << endl;
   for (auto v: v_list) {
      cout << "v: {" << v.xpos << "," << v.ypos << "}, ";
   }
   cout << endl;
   return make_shared<polygon> (vertex_list(v_list));
}

shape_ptr interpreter::make_rectangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if ((end - begin) != 2) {
      throw runtime_error("syntax error: rectangle");
   }
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<rectangle> (width, height);
}

shape_ptr interpreter::make_square (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if ((end - begin) != 1) throw runtime_error("syntax error: square");
   return make_shared<square> (GLfloat(stod(*begin)));
}

shape_ptr interpreter::make_diamond (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if ((end - begin) != 2) {
      throw runtime_error("syntax error: diamond");
   }
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<diamond> (width, height);
}

shape_ptr interpreter::make_triangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if ((end - begin) != 6) {
      throw runtime_error("syntax error: triangle");
   }
   GLfloat x0,y0,x1,y1,x2,y2;
   x0 = stod(*begin++);
   y0 = stod(*begin++);
   vertex v0{x0,y0};
   x1 = stod(*begin++);
   y1 = stod(*begin++);
   vertex v1{x1,y1};
   x2 = stod(*begin++);
   y2 = stod(*begin);
   vertex v2{x2,y2};
   return (make_shared<triangle>(v0, v1,v2));
}

shape_ptr interpreter::make_right_triangle (param begin, param end) {
   if ((end - begin) != 2) {
      throw runtime_error("syntax error: right_triangle");
   }
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<right_triangle> (width, height);
}
shape_ptr interpreter::make_isosceles (param begin, param end) {
   if ((end - begin) != 2) { 
      throw runtime_error("syntax error: isosceles");
   }
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<isosceles> (width, height);
}
shape_ptr interpreter::make_equilateral (param begin, param end) {
   if ((end - begin) != 1) {
      throw runtime_error("syntax error: equilateral");
   }
   GLfloat width;
   width = stod(*begin++);
   return make_shared<equilateral> (width);
}
