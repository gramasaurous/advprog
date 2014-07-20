// $Id: insertlist.cpp,v 1.42 2014-04-24 14:10:53-07 - - $

//
// List insertion algorithm.
// Insert nodes into a singly-linked list using only operator<
// to form comparisons.  Do not insert elements that already
// exist.
//

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename Type>
struct xless {
   bool operator() (const Type& left, const Type& right) const {
      return left < right;
   }
};

template <typename Type>
struct xgreater {
   bool operator() (const Type& left, const Type& right) const {
      return left > right;
   }
};


template <typename element, class Less=xless<element>>
struct linked_list {
   struct node {
      element elt;
      node* link;
      node (const element& elt_, node* link_): elt(elt_), link(link_) {}
   };
   Less less;
   node* head = nullptr;

   linked_list(){} // Needed because default is suppressed.
   linked_list (const linked_list&) = delete;
   linked_list& operator= (const linked_list&) = delete;

   void insert_ascending (const element& newelt) {
      node** curr = &head;
      while (*curr != nullptr and less ((*curr)->elt, newelt)) {
         curr = &(*curr)->link;
      }
      if (*curr == nullptr or less (newelt, (*curr)->elt)) {
         *curr = new node (newelt, *curr);
      }
   }

   element& front() { return head->elt; }

   void pop_front() {
      if (head == nullptr) {
         throw underflow_error ("linked_list<>::pop_front()");
      }
      node* old = head;
      head = head->link;
      delete old;
   }
};


template <typename element, class Less=xless<element>>
void process (int argc, char** argv, const string& label) {
   linked_list<string,Less> list;
   for (char** argp = &argv[1]; argp != &argv[argc]; ++argp) {
      cout << label << ": Insert: " << *argp << endl;
      list.insert_ascending (*argp);
   }
   while (list.head != nullptr) {
      cout << label << ": Sorted: " << list.front() << endl;
      list.pop_front();
   }
   cout << endl;
}

int main (int argc, char** argv) {
   process<string> (argc, argv, "Default");
   process<string,xgreater<string>> (argc, argv, "Greater");
   return 0;
}

/*
//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind --log-file=insertlist.out.log \
//TEST//       insertlist foo bar baz qux quux zxcvbnm asdfg qwerty \
//TEST//       bar baz foo quux qwerty hello hello 1234567890 \
//TEST//       >insertlist.out 2>&1
//TEST// mkpspdf insertlist.ps insertlist.cpp* insertlist.out*
*/
