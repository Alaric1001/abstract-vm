#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer/Token.hpp"
#include "utils/Stack.hpp"
#include "vm/ExecActions.hpp"

#include <deque>
#include <vector>

namespace parser {
bool syntax_checks(const std::deque<lexer::Token> &tokens);
void check_line(std::deque<lexer::Token>::const_iterator begin,
                std::deque<lexer::Token>::const_iterator end);
void parse_and_exec_line(std::deque<lexer::Token> &, exec::Stack &);
}  // namespace parser

#endif  // PARSER_HPP
