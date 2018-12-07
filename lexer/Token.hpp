#pragma once
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "utils/Dump.hpp"

namespace lexer {
class Token : public utils::IDumpable {
 public:
  enum class Type { Unknown, Blank, Instruction, Value, Newline, Numeric, OpeningBrace, ClosingBrace, Dot, Sign };

 private:
  Type m_type;
  const std::string m_value;

 public:
  Token() = default;
  Token(const Token&) = default;
  Token(Type, const std::string &);
  Token(Type, std::string &&);
  Token(Type);
  void dump(std::ostream &, bool verbose = true) const override;

  auto type() const { return m_type; }
  const auto &value() const { return m_value; }

  bool operator==(const Token &) const;
};

}  // namespace lexer
#endif  // TOKEN_HPP
