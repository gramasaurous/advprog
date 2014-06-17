// $Id: util.tcc,v 1.3 2014-06-11 13:49:31-07 - - $

template <typename item_t>
ostream& operator<< (ostream& out, const vector<item_t>& vec) {
   string space = "";
   for (const auto& item: vec) {
      out << space << item;
      space = " ";
   }
   return out;
}

