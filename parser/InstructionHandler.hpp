#pragma once
#ifndef INSTRUCTIONHANDLER_HPP
#define INSTRUCTIONHANDLER_HPP

#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

namespace parser {

class InstructionHandler : public Handler {
 private:
  static InstructionHandler s_instance;

  const std::string *m_last_instruction_processed = nullptr;

  const pattern::Pattern& get_pattern(const lexer::Token&) const override;
  void do_check(iterator i, iterator end) override;

  explicit InstructionHandler() = default;
  InstructionHandler &operator=(const InstructionHandler&) = default;
  InstructionHandler(const InstructionHandler&) = default;

 public:
  std::unique_ptr<const exec::IExecElem> parse(iterator,
                                               iterator) const override;

  const std::string *last_instruction_processed() const ;
  static InstructionHandler& instance();
};

}  // namespace parser

#endif  // INSTRUCTIONHANDLER_HPP
