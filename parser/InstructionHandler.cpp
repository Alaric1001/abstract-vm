#include "parser/InstructionHandler.hpp"
#include <cassert>

namespace parser {

const pattern::Pattern InstructionHandler::s_pattern{
    {LexerToken::Instruction}, {LexerToken::Blank}, {LexerToken::Value}};

void InstructionHandler::check(Handler::iterator i, Handler::iterator end) {
  int j = 0;
  for (auto &type : s_pattern) {
    if (i == end) throw ParseError(ParseError::UnexpectedEOF);
    ++m_token_processed;
    if (j == 1 and (i->value() != "assert" and i->value() != "push")) return;
    if (type == *i) throw ParseError(ParseError::UnexpectedToken);
    ++i;
    ++j;
  }
  --i;
  auto *value = get_handler(*i);
  assert(value);
  value->check(i, end);
  m_token_processed += value->token_processed();
}
}  // namespace parser
