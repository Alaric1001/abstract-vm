#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer/Token.hpp"

#include <deque>
#include <vector>

namespace exec {
  class IExecElem {};
}

namespace parser {
bool syntax_checks(const std::deque<lexer::Token> &tokens);
std::unique_ptr<const exec::IExecElem> parse_line(std::deque<lexer::Token> &);
}  // namespace parser

#endif  // PARSER_HPP
