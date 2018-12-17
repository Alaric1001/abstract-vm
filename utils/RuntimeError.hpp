#ifndef RUNTIMEERROR_HPP
#define RUNTIMEERROR_HPP

#include <exception>

#include <string>

namespace utils {

class RuntimeError : public std::exception {
 private:
  std::string m_error;

  RuntimeError &operator=(const RuntimeError&) = delete;
 public:
  RuntimeError() = delete;
  RuntimeError(const RuntimeError&) = default;
  RuntimeError(const char *);
  const char *what() const noexcept override;
};

class DivisionByZero : public RuntimeError {
 private:
  static const char *s_messages[2];

 public:
  enum class Type { Div, Mod };
  DivisionByZero(Type);
};

}  // namespace utils

#endif  // RUNTIMEERROR_HPP
