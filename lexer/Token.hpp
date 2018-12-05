#pragma once
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "utils/Dump.hpp"

namespace lexer {
class Token : public utils::IDumpable {
  public:
  enum class Type {Blank, Instruction, Value, Separator, Numeric, Brace};

  private:
  Type m_type;
  const std::string m_value;

  public:
  Token() = default;
  Token(Type, const std::string &);
  void dump(std::ostream &) const override;
};

} // namespace lexer
#endif // TOKEN_HPP
