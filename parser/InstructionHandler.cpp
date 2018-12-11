#include "parser/InstructionHandler.hpp"
#include "parser/Errors.hpp"
#include "parser/ValueHandler.hpp"

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
  if (i->type() != lexer::Token::Type::Value) return;
  auto *val_handler = ValueHandler::instance();
  try {
    val_handler->check(i, end);
    m_token_processed += val_handler->token_processed();
  } catch (const ParseError &e) {
    throw e;
  }
}

const std::unique_ptr<InstructionHandler> InstructionHandler::s_instance =
    std::make_unique<InstructionHandler>();

}  // namespace parser
