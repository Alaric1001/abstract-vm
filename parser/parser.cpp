#include "parser/parser.hpp"
#include "parser/InstructionHandler.hpp"

#include <iostream>

namespace parser {
bool syntax_checks(const std::deque<lexer::Token> &tokens) {
  bool ret  =true;
  auto it = tokens.cbegin();
  auto end = tokens.cend();
  auto *inst_hand = InstructionHandler::instance();
  while (it < end) {
    try {
      inst_hand->check(it, end);
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
      ret = false;
    }
    it += inst_hand->token_processed();
    while (it < end && it->type() != lexer::Token::Type::Newline) {
      if (it->type() != lexer::Token::Type::Blank) {
        std::cerr << "Nope" << '\n';
        ret = false;
      }
      ++it;
    }
    if (it < end)
      ++it;
  }
  return ret;
}

std::vector<int> parse(const std::deque<lexer::Token> &tokens) {
  syntax_checks(tokens);
  return {};
}
}  // namespace parser
