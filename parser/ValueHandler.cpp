#include "parser/ValueHandler.hpp"
#include <cassert>

namespace parser {

ValueHandler ValueHandler::s_instance = ValueHandler();

using LexerToken = lexer::Token::Type;
const pattern::Pattern int_pattern{
    pattern::get_token<pattern::Eq>(LexerToken::Value),
    pattern::get_token<pattern::Eq>(LexerToken::OpeningBrace),
    pattern::get_token<pattern::Eq>(LexerToken::Sign, true),
    pattern::get_token<pattern::Eq>(LexerToken::Numeric),
    pattern::get_token<pattern::Eq>(LexerToken::ClosingBrace),
};

const pattern::Pattern double_pattern{
    pattern::get_token<pattern::Eq>(LexerToken::Value),
    pattern::get_token<pattern::Eq>(LexerToken::OpeningBrace),
    pattern::get_token<pattern::Eq>(LexerToken::Sign, true),
    pattern::get_token<pattern::Eq>(LexerToken::Numeric, true),
    pattern::get_token<pattern::Eq>(LexerToken::Dot),
    pattern::get_token<pattern::Eq>(LexerToken::Numeric),
    pattern::get_token<pattern::Eq>(LexerToken::ClosingBrace),
};

const pattern::Pattern &ValueHandler::get_pattern(const lexer::Token &t) const {
  if (t.value() != "float" and t.value() != "double") return int_pattern;
  return double_pattern;
}

std::unique_ptr<const exec::IExecElem> ValueHandler::parse(
    Handler::iterator it, Handler::iterator) const {
  static const char *types[5] = { "int8", "int16", "int32", "float", "double" };
  exec::IOperand::OperandType optype;
  for (int i = 0; i < 5; ++i) {
    if (it->value() == types[i]) {
      optype = static_cast<exec::IOperand::OperandType>(i);
      break;
    }
    assert(i != 4);
  }
  std::string val;
  ++it;
  while ((++it)->type() != lexer::Token::Type::ClosingBrace)
    val += it->value();
  return std::make_unique<exec::ExecOperand>(std::move(val), optype);
}

}  // namespace parser
