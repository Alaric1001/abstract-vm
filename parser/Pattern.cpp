#include "parser/Pattern.hpp"

namespace parser {
namespace pattern {

bool Eq::operator==(const lexer::Token& token) const {
  return m_ref == token.type();
}

bool Or::operator==(const lexer::Token& token) const {
  for (const auto& ref : m_refs) {
    if (*ref == token) return true;
  }
  return false;
}

}  // namespace pattern
}  // namespace parser
