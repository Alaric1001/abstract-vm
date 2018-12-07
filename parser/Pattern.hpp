#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "lexer/Token.hpp"

#include <vector>

namespace parser {
namespace pattern {

class Token {
 private:
  bool m_optional;

 public:
  virtual ~Token() = default;
  Token(bool optional) : m_optional(optional) {}

  bool optional() const { return m_optional; }

  virtual bool operator==(const lexer::Token& token) const = 0;
  bool operator!=(const lexer::Token& token) const {
    return !(operator==(token));
  }
};

class Eq : public Token {
 private:
  lexer::Token::Type m_ref;

 public:
  Eq(lexer::Token::Type ref, bool optional = false)
      : Token(optional), m_ref(ref) {}

  bool operator==(const lexer::Token& token) const override;
};

using Pattern = std::vector<std::unique_ptr<Token>>;

}  // namespace pattern
}  // namespace parser

#endif  // TEMPLATE_HPP
