#pragma once
#ifndef INSTRUCTIONHANDLER_HPP
#define INSTRUCTIONHANDLER_HPP

#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

namespace parser {

class InstructionHandler : public Handler {
 private:
  static InstructionHandler s_instance;
  const pattern::Pattern& get_pattern(const lexer::Token&) const override;
  void do_check(iterator begin, iterator i, iterator end) override;

 public:
  std::unique_ptr<const exec::IExecElem> parse(iterator,
                                               iterator) const override;

  static InstructionHandler& instance() { return s_instance; }
};

}  // namespace parser

#endif  // INSTRUCTIONHANDLER_HPP
