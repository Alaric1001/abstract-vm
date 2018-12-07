#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "lexer/Token.hpp"

#include <vector>

namespace parser {
namespace pattern {

class PatternToken {
 private:
  using LexerToken = lexer::Token::Type;
  LexerToken m_type;
  bool m_mandatory;
  std::string m_value;

 public:
  PatternToken() = delete;
  PatternToken(LexerToken type, bool mandatory = true, std::string&& val = "")
      : m_type(type), m_mandatory(mandatory), m_value(std::move(val)) {}

  bool mandatory() const { return m_mandatory; }
  auto type() const { return m_type; }
  const auto &value() const { return m_value; }

  bool operator==(const lexer::Token& token) const {
    if (m_value.empty()) return m_type == token.type();
    return m_type == token.type() and token.value() == m_value;
  }
};

using Pattern = std::vector<PatternToken>;
}  // namespace pattern
}  // namespace parser

#endif  // TEMPLATE_HPP
