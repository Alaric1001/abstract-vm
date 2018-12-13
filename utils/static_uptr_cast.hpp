#ifndef STATIC_UPTR_CAST_HPP
#define STATIC_UPTR_CAST_HPP

#include <memory>

namespace utils {
template <typename From, typename To>
std::unique_ptr<To> static_uptr_cast(std::unique_ptr<From>&& old) {
  return std::unique_ptr<To>(static_cast<To*>(old.release()));
}
}  // namespace utils

#endif  // STATIC_UPTR_CAST_HPP
