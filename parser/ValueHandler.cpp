#include "parser/ValueHandler.hpp"
#include <cassert>

namespace parser {

std::unique_ptr<ValueHandler> ValueHandler::s_instance =
    std::make_unique<ValueHandler>();

using LexerToken = lexer::Token::Type;
const pattern::Pattern int_pattern{
    std::make_unique<pattern::Eq>(LexerToken::Value),
    std::make_unique<pattern::Eq>(LexerToken::OpeningBrace),
    std::make_unique<pattern::Eq>(LexerToken::Sign, true),
    std::make_unique<pattern::Eq>(LexerToken::Numeric),
    std::make_unique<pattern::Eq>(LexerToken::ClosingBrace),
};

const pattern::Pattern double_pattern{
    std::make_unique<pattern::Eq>(LexerToken::Value),
    std::make_unique<pattern::Eq>(LexerToken::OpeningBrace),
    std::make_unique<pattern::Eq>(LexerToken::Sign, true),
    std::make_unique<pattern::Eq>(LexerToken::Numeric, true),
    std::make_unique<pattern::Eq>(LexerToken::Dot),
    std::make_unique<pattern::Eq>(LexerToken::Numeric),
    std::make_unique<pattern::Eq>(LexerToken::ClosingBrace),
};

const pattern::Pattern &ValueHandler::get_pattern(const lexer::Token &t) const {
  if (t.value() != "float" and t.value() != "double") return int_pattern;
  return double_pattern;
}

}  // namespace parser
