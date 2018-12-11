#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "lexer/Token.hpp"

#include <exception>
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
  ParseError(Err err) : m_err(err) {}
  ParseError(Err err, const lexer::Token &tok) : m_err(err), m_token(&tok) {}
  const auto *token() const { return m_token; }
  const char *what() const noexcept {
    static const char *messages[] = {"Unexpected EOF", "Unexpected token"};
    return messages[static_cast<int>(m_err)];
  }
};
}  // namespace parser

#endif  // ERRORS_HPP
