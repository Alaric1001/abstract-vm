#pragma once
#ifndef TO_NUMERIC_HPP
#define TO_NUMERIC_HPP

#include <string>
#include <limits>
#include <iostream>

namespace utils {
template <typename T>
T to_numeric(const std::string&);

enum class NumState {
  InBounds,
  Overflow,
  Underflow
};

}  // namespace utils

#endif  // TO_NUMERIC_HPP
