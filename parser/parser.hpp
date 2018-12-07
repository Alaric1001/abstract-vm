#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer/Token.hpp"

#include <deque>
#include <vector>

namespace parser {
std::vector<int> parse(const std::deque<lexer::Token> &);
}  // namespace parser

#endif  // PARSER_HPP
