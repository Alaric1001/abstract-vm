#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>

namespace parser {
class ParseError : public std::exception {
 public:
  enum class Err { UnexpectedEOF, UnexpectedToken };

 private:
  static constexpr const char *messages[] = {"Unexpected EOF",
                                             "Unexpected token"};
  Err m_err;

 public:
  ParseError() = delete;
  ParseError(Err err) : m_err(err) {}
  const char *what() const noexcept {
    return messages[static_cast<int>(m_err)];
  }
};
}  // namespace parser

#endif  // ERRORS_HPP
