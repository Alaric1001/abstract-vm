#include "parser/parser.hpp"
#include "parser/Errors.hpp"
#include "parser/InstructionHandler.hpp"

#include "utils/static_uptr_cast.hpp"
#include "vm/globals.hpp"

#include <cassert>
#include <iostream>

namespace parser {

using iterator = std::deque<lexer::Token>::const_iterator;
using TokenType = lexer::Token::Type;

void next_instruction(iterator &it, iterator end) {
  while (it < end and it->type() != TokenType::Instruction) {
    if (it->type() == TokenType::Newline) globals::LineCounter::increment();
    ++it;
  }
}

void next_line(iterator &it, iterator end) {
  while (it != end and it->type() != TokenType::Newline) ++it;
  if (it != end) ++it;
}

void skip_spaces_and_nl(iterator &it, iterator end) {
  while (it != end and
         (it->type() == TokenType::Newline or it->type() == TokenType::Blank)) {
    if (it->type() == lexer::Token::Type::Newline)
      globals::LineCounter::increment();
    ++it;
  }
}

void check_line(iterator begin, iterator end) {
  // for (auto i = begin; i != end; ++i) {
  //  i->dump(std::cerr);
  //  std::cerr << ", ";
  //}
  // std::cerr << "\n";
  skip_spaces_and_nl(begin, end);
  if (begin < end) InstructionHandler::instance().check(begin, end);
}

bool syntax_checks(const std::deque<lexer::Token> &tokens) {
  bool correct = true;
  bool contains_exit = false;
  auto it = tokens.cbegin();
  auto end = tokens.cend();
  auto &inst_hand = InstructionHandler::instance();
  globals::LineCounter::reset();
  while (it < end) {
    skip_spaces_and_nl(it, end);
    if (it >= end) break;
    try {
      inst_hand.check(it, end);
      it += inst_hand.token_processed();
      const std::string *last_instruction_processed =
          inst_hand.last_instruction_processed();
      if (last_instruction_processed && *last_instruction_processed == "exit")
        contains_exit = true;
    } catch (const ParseError &e) {
      std::cerr << "Syntax error L." << globals::LineCounter::count() << ": ";
      e.display_err(std::cerr);
      next_line(it, end);
      correct = false;
    }
    globals::LineCounter::increment();
  }
  if (not contains_exit)
    std::cerr << "Syntax error: missing correct exit statement\n";
  return correct and contains_exit;
}

void parse_and_exec_line(std::deque<lexer::Token> &tokens, exec::Stack &stack) {
  auto it = tokens.cbegin();
  auto end = tokens.cend();
  assert(it < end);
  next_instruction(it, end);
  if (it >= end) return;
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
