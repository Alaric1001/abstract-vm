#include "parser/Errors.hpp"
namespace parser {

ParseError::ParseError(Err err) : m_err(err) {}

ParseError::ParseError(Err err, const lexer::Token &tok)
    : m_err(err), m_token(&tok) {}

const char *ParseError::what() const noexcept {
  static const char *messages[] = {"Unexpected EOF", "Unexpected token"};
  return messages[static_cast<int>(m_err)];
}

void ParseError::display_err(std::ostream &os) const {
  os << what();
  if (m_token) {
    os << " ";
    m_token->dump(os, false);
  }
  os << '\n';
}
}  // namespace parser
