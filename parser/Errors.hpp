#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "lexer/Token.hpp"

#include <exception>
#include <ostream>
#include <sstream>

namespace parser {
class ParseError : public std::exception {
 public:
  enum class Err { UnexpectedEOF, UnexpectedToken };

 private:
  Err m_err;
  const lexer::Token *m_token = nullptr;

 public:
  ParseError() = delete;
  ParseError(const ParseError &) = default;
  ParseError &operator=(const ParseError &) = delete;

  ParseError(Err err);
  ParseError(Err err, const lexer::Token &tok);

  const char *what() const noexcept override;
  void display_err(std::ostream &os) const;
};
}  // namespace parser

#endif  // ERRORS_HPP
