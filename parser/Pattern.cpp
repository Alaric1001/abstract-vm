#include "parser/Pattern.hpp"

namespace parser {
namespace pattern {

bool Eq::operator==(const lexer::Token& token) const {
  return m_ref == token.type();
}

bool Eq::operator==(const Eq& token) const {
  return m_ref == token.ref() && this->optional() == token.optional();
}

}  // namespace pattern
}  // namespace parser
