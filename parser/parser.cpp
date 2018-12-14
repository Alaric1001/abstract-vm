#include "parser/parser.hpp"
#include "parser/Errors.hpp"
#include "parser/InstructionHandler.hpp"

#include "utils/static_uptr_cast.hpp"
#include "vm/globals.hpp"

#include <cassert>
#include <iostream>

namespace parser {

void next_instruction(std::deque<lexer::Token>::const_iterator &it,
                      std::deque<lexer::Token>::const_iterator end) {
  while (it < end and it->type() != lexer::Token::Type::Instruction) {
    if (it->type() == lexer::Token::Type::Newline)
      globals::LineCounter::increment();
    ++it;
  }
}

void next_line(std::deque<lexer::Token>::const_iterator &it,
               std::deque<lexer::Token>::const_iterator end) {
  while (it != end and it->type() != lexer::Token::Type::Newline) ++it;
  if (it != end) ++it;
}

void skip_spaces_and_nl(std::deque<lexer::Token>::const_iterator &it,
                        std::deque<lexer::Token>::const_iterator end) {
  while (it != end and (it->type() == lexer::Token::Type::Newline or
                        it->type() == lexer::Token::Type::Blank)) {
    if (it->type() == lexer::Token::Type::Newline)
      globals::LineCounter::increment();
    ++it;
  }
}

bool syntax_checks(const std::deque<lexer::Token> &tokens) {
  bool ret = true;
  auto it = tokens.cbegin();
  auto end = tokens.cend();
  auto &inst_hand = InstructionHandler::instance();
  globals::LineCounter::reset();
  while (it < end) {
    skip_spaces_and_nl(it, end);
    try {
      inst_hand.check(it, end);
      it += inst_hand.token_processed();
    } catch (const ParseError &e) {
      std::cerr << "Syntax error L." << globals::LineCounter::count() << ": "
                << e.what();
      if (e.token()) {
        std::cerr << " ";
        e.token()->dump(std::cerr, false);
      }
      std::cerr << '\n';
      next_line(it, end);
      ret = false;
    }
    globals::LineCounter::increment();
  }
  return ret;
}

void parse_and_exec_line(std::deque<lexer::Token> &tokens, exec::Stack &stack) {
  auto it = tokens.cbegin();
  auto end = tokens.cend();
  assert(it < end);
  next_instruction(it, end);
  auto action = InstructionHandler::instance().parse(it, end);
  try {
    static_cast<const exec::IExecAction *>(action.get())->execute(stack);
  } catch (utils::RuntimeError &e) {
    throw;
  }
  next_line(it, end);
  tokens.erase(tokens.cbegin(), it);
}

}  // namespace parser
