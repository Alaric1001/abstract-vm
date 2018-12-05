
#pragma once
#ifndef DUMP_HPP
#define DUMP_HPP

#include <ostream>
#include <iterator>

namespace utils {

class IDumpable {
  public:
  virtual ~IDumpable() = default;
  virtual void dump(std::ostream &) const = 0;
};

template <class Collection>
void dump_objects(std::ostream &out, const Collection &collection) {
  out << "{ ";
  auto end = collection.cend();
  for (auto i = collection.cbegin(); i < end; ++i) {
    i->dump(out);
    out << (end - i == 1 ? " " : ", ");
  }
  out << "}";
}

} // namespace utils
#endif
