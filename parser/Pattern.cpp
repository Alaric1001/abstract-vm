#include "parser/Pattern.hpp"

namespace parser {
namespace pattern {

Token::Token(bool optional) : m_optional(optional) {}

bool Token::optional() const { return m_optional; }

bool Token::operator!=(const lexer::Token& token) const {
  return !(operator==(token));
}
Eq::Eq(lexer::Token::Type ref, bool optional)
    : Token(optional), m_ref(ref) {}

lexer::Token::Type Eq::ref() const { return m_ref; }
bool Eq::operator==(const lexer::Token& token) const {
  return m_ref == token.type();
}

bool Eq::operator==(const Eq& token) const {
  return m_ref == token.ref() && this->optional() == token.optional();
}

}  // namespace pattern
}  // namespace parser
