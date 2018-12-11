#ifndef TO_NUMERIC_HPP
#define TO_NUMERIC_HPP

#include <string>

namespace utils {
template <typename T>
T to_numeric(const std::string&);

template <>
int8_t to_numeric<int8_t>(const std::string& s) {
  int v;
  try {
    v = std::stoi(s);
  } catch (std::out_of_range&) {
    throw Overflow;
  }
  if (v > INT8_MAX or v < INT8_MIN) throw Overflow;
  return v;
}

template <>
int32_t to_numeric<int32_t>(const std::string& s) {
  try {
    return std::stoi(s);
  } catch (std::out_of_range&) {
    throw Overflow;
  }
}

template <>
int64_t to_numeric<int64_t>(const std::string& s) {
  try {
    return std::stol(s);
  } catch (std::out_of_range&) {
    throw Overflow;
  }
}

template <>
float to_numeric<float>(const std::string& s) {
  try {
    return std::stof(s);
  } catch (std::out_of_range&) {
    throw Overflow;
  }
}

template <>
double to_numeric<double>(const std::string& s) {
  try {
    return std::stod(s);
  } catch (std::out_of_range&) {
    throw Overflow;
  }
}
}  // namespace utils

#endif  // TO_NUMERIC_HPP
