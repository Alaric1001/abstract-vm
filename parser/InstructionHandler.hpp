#pragma once
#ifndef INSTRUCTIONHANDLER_HPP
#define INSTRUCTIONHANDLER_HPP

#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

namespace parser {

class InstructionHandler : public Handler {
 private:
  using LexerToken = lexer::Token::Type;
  static const pattern::Pattern s_pattern;

 public:
  void check(Handler::iterator i, Handler::iterator end) override;
};

}  // namespace parser

#endif  // INSTRUCTIONHANDLER_HPP
