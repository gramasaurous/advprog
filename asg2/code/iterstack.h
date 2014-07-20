// Graham Greving
// ggreving@ucsc.edu
// asg2: iterstack.h

// The class std::stack does not provide an iterator, which is
// needed for this class.  So, like std::stack, class iterstack
// is implemented on top of a container.
// 
// We use private inheritance because we want to restrict
// operations only to those few that are approved.  All functions
// are merely inherited from the container, with only ones needed
// being exported as public.
// 
// No implementation file is needed because all functions are
// inherited, and the convenience functions that are added are
// trivial, and so can be inline.
//
// Any underlying container which supports the necessary operations
// could be used, such as vector, list, or deque.
// 

#ifndef __ITERSTACK_H__
#define __ITERSTACK_H__

#include <vector>
using namespace std;

template <typename value_type>
class iterstack: private vector<value_type> {
   private:
      using stack_t = vector<value_type>;
      using stack_t::crbegin;
      using stack_t::crend;
      using stack_t::push_back;
      using stack_t::pop_back;
      using stack_t::back;
      using const_iterator = typename stack_t::const_reverse_iterator;
   public:
      using stack_t::clear;
      using stack_t::empty;
      using stack_t::size;
      inline const_iterator begin() {return crbegin();}
      inline const_iterator end() {return crend();}
      inline void push (const value_type& value) {push_back (value);}
      inline void pop() {pop_back();}
      inline const value_type& top() const {return back();}
};

#endif

