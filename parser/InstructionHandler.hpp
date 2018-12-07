#pragma once
#ifndef INSTRUCTIONHANDLER_HPP
#define INSTRUCTIONHANDLER_HPP

#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

namespace parser {

class InstructionHandler : public Handler {
 private:
  static const std::unique_ptr<InstructionHandler> s_instance;
  const pattern::Pattern& get_pattern(const lexer::Token&) const override;
  void do_check(iterator i, iterator end) override;
 public:

  static InstructionHandler *instance() { return s_instance.get(); }
};

}  // namespace parser

#endif  // INSTRUCTIONHANDLER_HPP
