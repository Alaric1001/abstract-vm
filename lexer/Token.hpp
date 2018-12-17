#pragma once
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "utils/Dump.hpp"

namespace lexer {
class Token : public utils::IDumpable {
 public:
  enum class Type {
    Unknown,
    Blank,
    Instruction,
    Value,
    Newline,
    Numeric,
    OpeningBrace,
    ClosingBrace,
    Dot,
    Sign
  };

 private:
  Type m_type;
  std::string m_value;

 public:
  Token() = default;
  Token(const Token &) = default;
  Token& operator=(const Token &) = default;

  Token(Type, const std::string &);
  Token(Type, std::string &&);
  Token(Type);
  void dump(std::ostream &, bool verbose = true) const override;

  Type type() const;
  const std::string &value() const; 

  bool operator==(const Token &) const;
};

}  // namespace lexer
#endif  // TOKEN_HPP
