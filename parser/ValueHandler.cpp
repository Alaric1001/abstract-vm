#include "parser/ValueHandler.hpp"
#include <cassert>

namespace parser {

std::unique_ptr<ValueHandler> ValueHandler::s_instance =
    std::make_unique<ValueHandler>();

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

}  // namespace parser
