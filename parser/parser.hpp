#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer/Token.hpp"
#include "vm/ExecActions.hpp"

#include <deque>
#include <vector>

namespace parser {
bool syntax_checks(const std::deque<lexer::Token> &tokens);
std::unique_ptr<const exec::IExecAction> parse_line(std::deque<lexer::Token> &);
}  // namespace parser

#endif  // PARSER_HPP
