#include "utils/to_numeric.hpp"

namespace utils {

template <typename T>
T to_numeric_small_ints(const std::string& s) {
  int v;
  try {
    v = std::stoi(s);
  } catch (std::out_of_range&) {
    throw;
  }
  if (v > std::numeric_limits<T>::max() or v < std::numeric_limits<T>::min())
    throw std::out_of_range("");
  return v;
}

template <>
int8_t to_numeric<int8_t>(const std::string& s) {
  try {
    return to_numeric_small_ints<int8_t>(s);
  } catch (std::out_of_range&) {
    throw;
  }
}

template <>
int16_t to_numeric<int16_t>(const std::string& s) {
  try {
    return to_numeric_small_ints<int16_t>(s);
  } catch (std::out_of_range&) {
    throw;
  }
}

template <>
int32_t to_numeric<int32_t>(const std::string& s) {
  try {
    return std::stoi(s);
  } catch (std::out_of_range&) {
    throw;
  }
}

template <>
float to_numeric<float>(const std::string& s) {
  try {
    return std::stof(s);
  } catch (std::out_of_range&) {
    throw;
  }
}

template <>
double to_numeric<double>(const std::string& s) {
  try {
    return std::stod(s);
  } catch (std::out_of_range&) {
    throw;
  }
}

}  // namespace utils
