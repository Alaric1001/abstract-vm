#include "utils/to_numeric.hpp"

namespace utils {

template <>
int8_t to_numeric<int8_t>(const std::string& s) {
  int v;
  try {
    v = std::stoi(s);
  } catch (std::out_of_range &e) {
    throw e;
  }
  if (v > INT8_MAX or v < INT8_MIN) throw std::out_of_range("");
  return v;
}

template <>
int32_t to_numeric<int32_t>(const std::string& s) {
  try {
    return std::stoi(s);
  } catch (std::out_of_range &e) {
    throw e;
  }
}

template <>
int64_t to_numeric<int64_t>(const std::string& s) {
  try {
    return std::stol(s);
  } catch (std::out_of_range &e) {
    throw e;
  }
}

template <>
float to_numeric<float>(const std::string& s) {
  try {
    return std::stof(s);
  } catch (std::out_of_range &e) {
    throw e;
  }
}

template <>
double to_numeric<double>(const std::string& s) {
  try {
    return std::stod(s);
  } catch (std::out_of_range &e) {
    throw e;
  }
}

} // namespace utils
