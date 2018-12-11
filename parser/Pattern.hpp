#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "lexer/Token.hpp"

#include <vector>

#include <iostream>
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
  bool operator==(const Eq& token) const;

  auto ref() const { return m_ref; }
};

using Pattern = std::vector<const Token*>;

template <typename T, typename... E>
const Token* get_token(E... args) {
  static std::vector<std::unique_ptr<T>> instances;

  std::unique_ptr<T> o = std::make_unique<T>(std::forward<E>(args)...);
  for (const auto& e : instances) {
    if (*e == *o) return e.get();
  }
  instances.push_back(std::move(o));
  return instances.back().get();
}

}  // namespace pattern
}  // namespace parser

#endif  // TEMPLATE_HPP
