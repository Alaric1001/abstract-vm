#include "lexer/lexer.hpp"
#include "lexer/LexerIterator.hpp"
#include "lexer/punctuation.hpp"

#include <algorithm>
#include <functional>
#include <array>
#include <cctype>
#include <iostream>

namespace lexer {

bool blank_check(LexerIterator &i, std::deque<Token> &container) {
  if (std::isblank(*i)) {
    auto blank_begin = i.iterator();
    i.next_word();
    container.emplace_back(Token::Type::Blank,
                           std::string(blank_begin, i.iterator()));
    return true;
  }
  return false;
}

bool punctuation_check(LexerIterator &it, std::deque<Token> &container) {
  Token::Type type = Token::Type::Unknown;
  switch (*it) {
    case '(': type = Token::Type::OpeningBrace; break;
    case ')': type = Token::Type::ClosingBrace; break;
    case '-': type = Token::Type::Sign; break;
    case '+': type = Token::Type::Sign; break;
    case '.': type = Token::Type::Dot; break;
  }
  if (type == Token::Type::Unknown) return false;
  container.emplace_back(type, std::string(1, *it));
  ++it;
  return true;
}

bool numeric_check(LexerIterator &it, std::deque<Token> &container) {
  auto start = it.iterator();
  while (it.iterator() < it.end() && std::isdigit(*it)) ++it;
  if (start == it.iterator())
    return false;
  container.emplace_back(Token::Type::Numeric, std::string(start, it.iterator()));
  return true;
}

bool keywords_check(LexerIterator &it, std::deque<Token> &container) {
  static const std::array<lexer::Token, 16> tokens{{
      {Token::Type::Instruction, "push"},
      {Token::Type::Instruction, "pop"},
      {Token::Type::Instruction, "dump"},
      {Token::Type::Instruction, "assert"},
      {Token::Type::Instruction, "add"},
      {Token::Type::Instruction, "sub"},
      {Token::Type::Instruction, "mul"},
      {Token::Type::Instruction, "div"},
      {Token::Type::Instruction, "mod"},
      {Token::Type::Instruction, "print"},
      {Token::Type::Instruction, "exit"},
      {Token::Type::Value, "int8"},
      {Token::Type::Value, "int16"},
      {Token::Type::Value, "int32"},
      {Token::Type::Value, "float"},
      {Token::Type::Value, "double"},
  }};
  for (const auto &e : tokens) {
    auto val_sz = e.value().size();
    if (it.iterator() + val_sz <= it.end() and
        std::equal(e.value().cbegin(), e.value().cend(), it.iterator())) {
      container.emplace_back(e);
      it += val_sz;
      return true;
    }
  }
  return false;
}

void lexe_line(const std::string &line, std::deque<Token> &container) {
  static const std::array<
      std::function<bool(LexerIterator &, std::deque<Token> &)>, 4>
      checks{{blank_check, punctuation_check, numeric_check, keywords_check}};
  LexerIterator i(line);

  while (i.iterator() < line.cend()) {
    if (*i == ';') break;
    auto checks_it = checks.cbegin();
    for (; checks_it < checks.cend(); ++checks_it)
      if ((*checks_it)(i, container)) break;
    if (checks_it == checks.cend()) {
      auto unknown_begin = i.iterator();
      i.next_blank();
      container.emplace_back(Token::Type::Unknown,
                             std::string(unknown_begin, i.iterator()));
    }
  }
  container.emplace_back(Token::Type::Newline, "\\n");
}

std::deque<Token> lexe(std::istream &input) {
  std::deque<Token> ret;

  for (std::string line; std::getline(input, line);) {
    lexe_line(line, ret);
  }
  return ret;
}

}  // namespace lexer
