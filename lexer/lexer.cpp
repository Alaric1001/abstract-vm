#include "lexer/lexer.hpp"
#include "lexer/LexerIterator.hpp"

#include <cctype>
#include <iostream>
#include <array>

namespace lexer {

bool blank_check(LexerIterator &i, std::deque<Token> &container) {
  if (std::isblank(*i)) {
    auto blank_begin = i.iterator();
    i.next_word();
    container.emplace_back(Token::Type::Blank, std::string(blank_begin, i.iterator()));
    return true;
  }
  return false;
}

bool do_nothing(LexerIterator &, std::deque<Token> &) {
  return true;
}

void lexe_line(const std::string &line, std::deque<Token>& container) {
  static const std::array<std::function<bool(LexerIterator&,
                                  std::deque<Token>&)>, 2>
                checks{{blank_check, do_nothing}};
  for (LexerIterator i(line); i.iterator() < line.cend(); ++i) {
    if (*i == ';')
      break;
    auto checks_it = checks.cbegin();
    for (; checks_it < checks.cend(); ++checks_it)
      if ((*checks_it)(i, container))
        break;
    if (checks_it == checks.cend()) {
      std::cerr << "Err!" << "\n";
      break;
    }
  }
}

std::deque<Token> lexe(std::istream &input) {
  std::deque<Token> ret;

  for (std::string line; std::getline(input, line);) {
    lexe_line(line, ret);
  }
  return ret;
}

} // namespace lexer
