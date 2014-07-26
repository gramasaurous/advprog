// Graham Greving
// ggreving@ucsc.edu
// listmap.tcc

#include "listmap.h"
#include "trace.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   TRACE ('l', (void*) this);
}

//
// listmap::empty()
//
template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::empty() const {
   return (anchor_.next == nullptr && anchor_.prev == nullptr);
}

//
// listmap::iterator listmap::begin()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::begin() {
   return iterator (anchor_.next);
}

//
// listmap::iterator listmap::end()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::end() {
   return iterator (anchor());
}

//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::insert (const value_type& pair) {
   TRACE ('l', &pair << "->" << pair);
   // make a node and set to anchor!
   //node n(nullptr, nullptr, pair);
   //anchor_.next = &n;
   //anchor_.prev = &n;
   Less less;

   node n(nullptr, nullptr, pair);
   
   if (empty()) {
      anchor_.next = &n;
      anchor_.prev = &n;
      cout << "new node: " << pair << endl; 
   } else {
      n.prev = anchor_.prev;
      anchor_.next = &n;
      cout << "new node: " << pair << endl; 
      cout << "at:" << &n; 
   }
   return iterator();
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) const {
   TRACE ('l', that);
   return iterator();
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   TRACE ('l', &*position);
   return iterator();
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   TRACE ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   TRACE ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   TRACE ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   TRACE ('l', where);
   where = where->prev;
   return *this;
}

//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}
