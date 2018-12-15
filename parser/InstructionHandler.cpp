#include "parser/InstructionHandler.hpp"
#include "parser/Errors.hpp"
#include "parser/ValueHandler.hpp"

#include "utils/static_uptr_cast.hpp"
#include "vm/ExecActions.hpp"

#include <cassert>
#include <memory>

namespace parser {

using LexerToken = lexer::Token::Type;
const pattern::Pattern single_instr_pattern{
    pattern::get_token<pattern::Eq>(LexerToken::Blank, true),
    pattern::get_token<pattern::Eq>(LexerToken::Instruction),
    pattern::get_token<pattern::Eq>(LexerToken::Blank, true),
    pattern::get_token<pattern::Eq>(LexerToken::Newline),
};

const pattern::Pattern instr_value_pattern{
    pattern::get_token<pattern::Eq>(LexerToken::Blank, true),
    pattern::get_token<pattern::Eq>(LexerToken::Instruction),
    pattern::get_token<pattern::Eq>(LexerToken::Blank),
    pattern::get_token<pattern::Eq>(LexerToken::Value),
    pattern::get_token<pattern::Eq>(LexerToken::Blank, true),
    pattern::get_token<pattern::Eq>(LexerToken::Newline),
};

const pattern::Pattern &InstructionHandler::get_pattern(
    const lexer::Token &t) const {
  if (t.value() != "assert" and t.value() != "push")
    return single_instr_pattern;
  return instr_value_pattern;
}

void InstructionHandler::do_check(Handler::iterator, Handler::iterator i,
                                  Handler::iterator end) {
  if (i->type() == lexer::Token::Type::Instruction) {
    m_last_instruction_processed = &(i->value());
    return ;
  }
  if (i->type() != lexer::Token::Type::Value) return;
  auto &val_handler = ValueHandler::instance();
  try {
    val_handler.check(i, end);
    m_token_processed += val_handler.token_processed();
  } catch (const ParseError &e) {
    throw e;
  }
}

std::unique_ptr<const exec::IExecElem> InstructionHandler::parse(
    Handler::iterator it, Handler::iterator end) const {
  auto simple_action = exec::ExecSimpleAction::create(it->value());
  if (simple_action) return simple_action;
  auto elem = ValueHandler::instance().parse(it + 2, end);
  auto operand =
      utils::static_uptr_cast<const exec::IExecElem, const exec::ExecOperand>(
          std::move(elem));
  return exec::ExecValueAction::create(it->value(), std::move(operand));
}

const std::string *InstructionHandler::last_instruction_processed() const {
  return m_last_instruction_processed;
}

InstructionHandler InstructionHandler::s_instance = InstructionHandler();

InstructionHandler &InstructionHandler::instance() { return s_instance; }
}  // namespace parser
