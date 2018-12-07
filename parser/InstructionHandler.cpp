#include "parser/InstructionHandler.hpp"
#include "parser/ValueHandler.hpp"

#include <cassert>
#include <memory>

namespace parser {

using LexerToken = lexer::Token::Type;
const pattern::Pattern single_instr_pattern{
    std::make_unique<pattern::Eq>(LexerToken::Instruction)};

const pattern::Pattern instr_value_pattern{
    std::make_unique<pattern::Eq>(LexerToken::Instruction),
    std::make_unique<pattern::Eq>(LexerToken::Blank),
    std::make_unique<pattern::Eq>(LexerToken::Value),
};

const pattern::Pattern &InstructionHandler::get_pattern(
    const lexer::Token &t) const {
  if (t.value() != "assert" and t.value() != "push")
    return single_instr_pattern;
  return instr_value_pattern;
}

void InstructionHandler::do_check(Handler::iterator i, Handler::iterator end) {
  if (m_token_processed != 1) return;
  auto *val_handler = ValueHandler::instance();
  try {
    val_handler->check(i, end);
    m_token_processed += val_handler->token_processed();
  } catch (std::exception &e) {
    throw e;
  }
}

const std::unique_ptr<InstructionHandler> InstructionHandler::s_instance =
    std::make_unique<InstructionHandler>();

}  // namespace parser
