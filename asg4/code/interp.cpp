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
#include "graphics.h"

map<string,interpreter::interpreterfn> interpreter::interp_map {
   {"define" , &interpreter::do_define },
   {"draw"   , &interpreter::do_draw   },
};

map<string,interpreter::factoryfn> interpreter::factory_map {
   {"text"     , &interpreter::make_text     },
   {"ellipse"  , &interpreter::make_ellipse  },
   {"circle"   , &interpreter::make_circle   },
   {"polygon"  , &interpreter::make_polygon  },
   {"rectangle", &interpreter::make_rectangle},
   {"square"   , &interpreter::make_square   },
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
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<ellipse> (width, height);
}

shape_ptr interpreter::make_circle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   return make_shared<circle> (GLfloat(stod(*begin)));
}

shape_ptr interpreter::make_polygon (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if (((end - begin) % 2) != 0) {
      throw runtime_error ("syntax error: odd number of inputs");
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
   for (auto v: v_list) {
      v.xpos -= x_avg;
      v.ypos -= y_avg;
      DEBUGF ('p', "v(" << v.xpos <<"," << v.ypos <<")");
   }
   // Here, all vertices exist around center 0,0
   // We will now sort them by their angle to the x-axis using
   // atan2(ypos,xpos) from cmath
   std::sort (v_list.begin(), v_list.end(),
      [](const vertex &a, const vertex &b){
      float degree_a = atan2(a.ypos, a.xpos) * 180 / M_PI;
      float degree_b = atan2(b.ypos, b.xpos) * 180 / M_PI;
      return (degree_a < degree_b);
   });
   return make_shared<polygon> (vertex_list(v_list));
}

shape_ptr interpreter::make_rectangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   for (auto i = begin; i != end; ++i) {
      DEBUGF('p', *i);
   }
   GLfloat width;
   GLfloat height;
   width = stod(*begin++);
   height = stod(*begin);
   return make_shared<rectangle> (width, height);
}

shape_ptr interpreter::make_square (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   for (auto i = begin; i != end; ++i) {
      DEBUGF('p', *i);
   }
   return make_shared<square> (GLfloat(stod(*begin)));
}

