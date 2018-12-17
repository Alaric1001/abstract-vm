#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "lexer/Token.hpp"

#include <memory>
#include <vector>

#include <iostream>
namespace parser {
namespace pattern {

class Token {
 private:
  bool m_optional;

 public:
  virtual ~Token() = default;
  Token() = delete;
  Token(const Token&) = delete;
  Token& operator=(const Token&) = delete;

  Token(bool optional);

  bool optional() const;

  virtual bool operator==(const lexer::Token& token) const = 0;
  bool operator!=(const lexer::Token& token) const;
};

class Eq : public Token {
 private:
  lexer::Token::Type m_ref;

 public:
  Eq() = delete;
  Eq(const Eq&) = delete;
  Eq& operator=(const Eq&) = delete;
  Eq(lexer::Token::Type ref, bool optional = false);

  bool operator==(const lexer::Token& token) const override;
  bool operator==(const Eq& token) const;

  decltype(m_ref) ref() const;
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
