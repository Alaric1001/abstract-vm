#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils/Dump.hpp"
#include "utils/Stack.hpp"
#include "vm/IOperand.hpp"

#include "vm/globals.hpp"

#include <iostream>
#include <sstream>

int main() {
  utils::Stack<std::unique_ptr<const exec::IOperand>> stack;
  std::stringstream input(
      "\n\n \npush int8(126)  \n\n\npush int32(0)\n mod\ndump\n exit");
  auto container = lexer::lexe(input);
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
  if (not parser::syntax_checks(container)) return (1);
  globals::LineCounter::reset();
  while (not container.empty()) {
    try {
      parser::parse_and_exec_line(container, stack);
    } catch (utils::RuntimeError &e) {
      std::cerr << e.what() << "\n";
      return (1);
    }
  }
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
}
