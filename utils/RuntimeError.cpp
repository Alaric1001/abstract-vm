#include "utils/RuntimeError.hpp"

#include "vm/globals.hpp"

#include <sstream>

namespace utils {
// RuntimeError
RuntimeError::RuntimeError(const char* s) {
  std::stringstream ss;
  ss << "Runtime Error L." << globals::LineCounter::count() << ": " << s;
  m_error = ss.str();
}

const char *RuntimeError::what() const noexcept { return m_error.c_str(); }

// DivisionByZero

const char *DivisionByZero::s_messages[2] = {
    "Can't perform division with operand 0",
    "Can't perform modulo with operand 0"};

DivisionByZero::DivisionByZero(Type type)
    : RuntimeError(s_messages[static_cast<int>(type)]) {}
}  // namespace utils
