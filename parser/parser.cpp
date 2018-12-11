#include "parser/parser.hpp"
#include "parser/Errors.hpp"
#include "parser/InstructionHandler.hpp"

#include <iostream>

namespace parser {

void next_line(std::deque<lexer::Token>::const_iterator &it,
               std::deque<lexer::Token>::const_iterator end) {
  while (it != end and it->type() != lexer::Token::Type::Newline) ++it;
  if (it != end) ++it;
}

void skip_spaces_and_nl(std::deque<lexer::Token>::const_iterator &it,
                        std::deque<lexer::Token>::const_iterator end) {
  while (it != end and (it->type() == lexer::Token::Type::Newline or
         it->type() == lexer::Token::Type::Blank))
    ++it;
}

bool syntax_checks(const std::deque<lexer::Token> &tokens) {
  bool ret = true;
  auto it = tokens.cbegin();
  auto end = tokens.cend();
  auto *inst_hand = InstructionHandler::instance();
  int line = 1;
  while (it < end) {
    skip_spaces_and_nl(it, end);
    std::cerr << it->value() << "\n";
    try {
      inst_hand->check(it, end);
      it += inst_hand->token_processed();
    } catch (const ParseError &e) {
      std::cerr << "Syntax error l." << line << ": " << e.what();
      if (e.token()) {
        std::cerr << " ";
        e.token()->dump(std::cerr, false);
      }
      std::cerr << '\n';
      next_line(it, end);
      ret = false;
    }
    ++line;
  }
  return ret;
}

std::unique_ptr<const exec::IExecElem> parse_line(std::deque<lexer::Token> &tokens) {
  
}

}  // namespace parser
