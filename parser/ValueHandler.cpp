#include "parser/ValueHandler.hpp"
#include <cassert>

namespace parser {

const pattern::Pattern ValueHandler::s_pattern{
    {LexerToken::Value}, {LexerToken::Punctuation, true, "("}, {}, {LexerToken::Punctuation, ")"}};
//TODO create an interface for PattenToken, with two son ftm: Simple and Or

void ValueHandler::check(Handler::iterator i, Handler::iterator end) {
  int j = 0;
  for (auto &type : s_pattern) {
    if (i == end) throw ParseError(ParseError::UnexpectedEOF);
    ++m_token_processed;
    if (j == 1 and (i->value() != "assert" and i->value() != "push")) return;
    if (i->type() != type.type()) throw ParseError(ParseError::UnexpectedToken);
    ++i;
    ++j;
  }
  auto *value = get_handler(*i);
  assert(value);
  value->check(i, end);
  m_token_processed += value->token_processed();
}
}  // namespace parser
