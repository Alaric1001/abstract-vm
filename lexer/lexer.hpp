#pragma once
#ifndef LEXE_HPP
#define LEXE_HPP

#include "lexer/Token.hpp"

#include <deque>
#include <istream>

namespace lexer {

std::deque<Token> lexe(std::istream &);

} // namespace lexer
#endif // LEXE_HPP
