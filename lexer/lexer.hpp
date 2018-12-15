#pragma once
#ifndef LEXE_HPP
#define LEXE_HPP

#include "lexer/Token.hpp"

#include <deque>
#include <istream>

namespace lexer {

std::deque<Token> lexe(std::istream &);
void lexe_line(const std::string &line, std::deque<Token> &container);

} // namespace lexer
#endif // LEXE_HPP
